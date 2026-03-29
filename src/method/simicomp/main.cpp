/*
 * main.cpp
 *
 *  Created on: Jan 29, 2026
 *      Author: pjarnot
 */
#include "method/simicomp/options.hpp"
#include "identification/simicomp.hpp"
#include "debug.hpp"
#include "dal/sequencereaderfasta.hpp"
#include "utils/threadpool.hpp"


#include <iostream>
#include <fstream>


using namespace nscsearch;
using namespace cbsearch;
using namespace std;


std::mutex simicomp_writer_mutex;

void save_fragment(ostream *output, string iheader, string isequence) {
	std::lock_guard<std::mutex> guard(simicomp_writer_mutex);
	*output << iheader;
	*output << "\n";
	*output << isequence;
	*output << "\n";
}

int identify_thread(std::map<size_t, int>* worker_ids, OptionsSc *iopt, ostream *output, string query_head, string query_seq, string hit_head, string hit_seq) {
	SimiComp sc;
	std::vector<identification_result_t> fragments = sc.identify(query_seq, hit_seq, iopt->get_similarity_threshold(), iopt->get_relative_threshold());
	for (identification_result_t fragment : fragments) {
		string db_fragment = hit_seq.substr(fragment.begin-1, fragment.end - fragment.begin + 1);
		save_fragment(output, hit_head, db_fragment);
	}
	return 0;
}

void scan_database(OptionsSc *iopt, istream *input, ostream *output, Sequence query) {
	int thread_count = iopt->get_thread_count() < 1 ? 1 : iopt->get_thread_count();
	ThreadPool thread_pool(thread_count);
	unique_ptr<SequenceReader> database_reader(new SequenceReaderFasta(iopt->get_database_file_path()));

	const int NUMBER_OF_TASKS_IN_WAITING_QUEUE_PER_THREAD = 20;
	while (database_reader->has_next_sequence()) {
		while (thread_pool.get_tasks_count() > (NUMBER_OF_TASKS_IN_WAITING_QUEUE_PER_THREAD * thread_count)) std::this_thread::sleep_for(std::chrono::microseconds(500));
		Sequence ds = database_reader->get_next_sequence();
		if (ds.get_sequence().length() == 0) {
			continue;
		}

		if (thread_count > 1) {
			std::future<int> x = thread_pool.enqueue(identify_thread, thread_pool.get_worker_ids(), iopt, output, query.get_header(), query.get_sequence(), ds.get_header(), ds.get_sequence());
		} else {
			identify_thread(nullptr, iopt, output, query.get_header(), query.get_sequence(), ds.get_header(), ds.get_sequence());
		}
	}

	while (thread_pool.get_tasks_count() > 0) std::this_thread::sleep_for(std::chrono::microseconds(500));

	thread_pool.dispose();
}

void run_simicomp(OptionsSc *iopt, istream *input, ostream *output) {
	unique_ptr<SequenceReader> query_reader(new SequenceReaderFasta(input));

	while (query_reader->has_next_sequence()) {
		Sequence next_sequence = query_reader->get_next_sequence();
		scan_database(iopt, input, output, next_sequence);
	}
}

istream *get_input(OptionsSc &opt) {
	if (opt.get_query_file_path().length() > 0) {
		return new ifstream(opt.get_query_file_path());
	}
	else {
		return &cin;
	}
}


ostream *get_output(OptionsSc &opt) {
	if (opt.get_output_file_path().length() > 0) {
		return new ofstream(opt.get_output_file_path());
	}
	else {
		return &cout;
	}
}


int open_database(OptionsSc &opt, ifstream &idatabase_stream) {
	idatabase_stream.open(opt.get_database_file_path());
	if (idatabase_stream.fail()) {
		cout << "Could not open file: " << opt.get_database_file_path() << "\n";
		return -1;
	}
	return 0;
}


void dispose_files(istream *input, ostream *output, ifstream &database_stream) {
	ifstream *input_file = dynamic_cast<ifstream*>(input);
	if (input_file != nullptr) {
		input_file->close();
	}
	delete input_file;

	ofstream *output_file = dynamic_cast<ofstream*>(output);
	if (output_file != nullptr) {
		output_file->close();
	}
	delete output_file;

	database_stream.close();
}


int main(int argc, char **argv) {
	try {
		OptionsSc opt;

		int status = opt.parse_options(argc, argv);
		if (status < 0)
			return status;

		subscribe_stacktrace(opt.get_debug_level());

		istream *input = get_input(opt);
		ostream *output = get_output(opt);
		ifstream database_stream;
		if (open_database(opt, database_stream) != 0) {
			dispose_files(input, output, database_stream);
			return -1;
		}

		run_simicomp(&opt, input, output);

		dispose_files(input, output, database_stream);
	}
	catch (std::logic_error &e) {
		cerr << e.what();
		return -1;
	}

    return 0;
}

