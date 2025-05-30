/*
 * main.cpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#include "dal/sequencereaderfasta.hpp"

#include "debug.hpp"

#include <iostream>
#include <fstream>

#include "../include/method/nscsearch.hpp"
#include "method/options.hpp"
#include "method/resultsoutput.hpp"

using namespace nscsearch;
using namespace std;


istream *get_input(Options &opt) {
	if (opt.get_query_file_path().length() > 0) {
		return new ifstream(opt.get_query_file_path());
	}
	else {
		return &cin;
	}
}


ostream *get_output(Options &opt) {
	if (opt.get_output_file_path().length() > 0) {
		return new ofstream(opt.get_output_file_path());
	}
	else {
		return &cout;
	}
}


int open_database(Options &opt, ifstream &idatabase_stream) {
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


void run_method(Options *opt, istream *input, ostream *output) {
	unique_ptr<SequenceReader> database_reader(new SequenceReaderFasta(opt->get_database_file_path()));
	unique_ptr<SequenceReader> query_reader(new SequenceReaderFasta(input));

	NscSearch search(opt, database_reader.get());
	ResultsOutput results_output(opt->get_sort_output_by(), opt->get_threshold());

	while (query_reader->has_next_sequence()) {
		Sequence next_sequence = query_reader->get_next_sequence();
		search.scan_database(next_sequence);
		results_t results = search.get_results();
		results.query_header = next_sequence.get_header();
		results_output.print_records(output, &results, opt->get_limit(), opt->get_output_format());
	}
}


int main(int argc, char **argv) {
	try {
		Options opt;

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

		run_method(&opt, input, output);

		dispose_files(input, output, database_stream);
	}
	catch (std::logic_error &e) {
		cerr << e.what();
		return -1;
	}

    return 0;
}

