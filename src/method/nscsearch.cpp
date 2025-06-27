/*
 * lcrsearch.cpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#include "alignment/nw/needlemanwunsch.hpp"
#include "alignment/og/onewayglobal.hpp"
#include "alignment/sw/smithwaterman.hpp"
#include "alignment/alignbase.hpp"
#include "utils/fasta.hpp"
#include "utils/stringutils.hpp"
#include "utils/threadpool.hpp"
#include "filters/kmer.hpp"
#include "debug.hpp"
#include "exceptions.hpp"

#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>

#include "../../include/method/nscsearch.hpp"
#include "identification/simicomp.hpp"
//#include "identification/frequencyidentificator.hpp"

using namespace nscsearch;
using namespace std;



NscSearch::NscSearch(Options *iopt, SequenceReader *idatabase_reader) {
	opt = iopt;
	database_reader = idatabase_reader;
}


NscSearch::~NscSearch() {

}


int scan_fasta_thread(std::map<size_t, int>* worker_ids, NscSearch *search, Sequence iquery_sequence, Sequence idatabase_sequence, Options* iopt, vector<AlignBase*> *abs, KmerFilter *ikmer_filter) {//float igap_open_score, float igap_extension_score) {
	int worker_id;

	if (worker_ids == nullptr) {
		worker_id = 0;
	}
	else {
		auto it = worker_ids->find(std::hash<std::thread::id>{}(std::this_thread::get_id()));
		assert(it != worker_ids->end());
		worker_id = it->second;
	}

	AlignBase *ab = (*abs)[worker_id];

	static int counter = 0;

	try {
		if (iopt->get_is_composition_identification()) {
			string query = iquery_sequence.get_sequence();
			string hit = idatabase_sequence.get_sequence();
			if (ikmer_filter->contain_similar_fragment(hit)) {
				SimiComp sc;
				std::vector<identification_result_t> fragments = sc.identify(query, hit, iopt->get_similarity_threshold(), iopt->get_relative_threshold());

				for (identification_result_t fragment : fragments) {
					ab->align(iquery_sequence.get_sequence(), idatabase_sequence.get_sequence().substr(fragment.begin-1, fragment.end - fragment.begin + 1), iopt->get_gap_open(), iopt->get_gap_extension());
					search->save_reported_record(ab->get_alignments()[0].query_alignment, ab->get_alignments()[0].midline_alignment, idatabase_sequence.get_header(), ab->get_alignments()[0].hit_alignment, ab->get_alignments()[0].score, ab->get_alignments()[0].similarity_score, ab->get_alignments()[0].identity, ab->get_alignments()[0].similarity, fragment.begin, fragment.end);
				}
			}
		}
		else if (dynamic_cast<OneWayGlobal *>(ab) != nullptr) {
//			ab->align(iquery_sequence.get_sequence(), idatabase_sequence.get_sequence(), iopt->get_gap_open(), iopt->get_gap_extension());
//			search->save_reported_record(ab->get_alignments()[0].query_alignment, ab->get_alignments()[0].midline_alignment, idatabase_sequence.get_header(), ab->get_alignments()[0].hit_alignment, ab->get_alignments()[0].score, ab->get_alignments()[0].similarity_score, ab->get_alignments()[0].identity, ab->get_alignments()[0].similarity, -1, -1);
			string query = iquery_sequence.get_sequence();
			string hit = idatabase_sequence.get_sequence();
//			SimiComp sc;
//			if (sc.contain_similar_fragment(query, hit, iopt->get_similarity_threshold())) {
			if (ikmer_filter->contain_similar_fragment(hit)) {
				ab->align(iquery_sequence.get_sequence(), idatabase_sequence.get_sequence(), iopt->get_gap_open(), iopt->get_gap_extension());
				search->save_reported_record(ab->get_alignments()[0].query_alignment, ab->get_alignments()[0].midline_alignment, idatabase_sequence.get_header(), ab->get_alignments()[0].hit_alignment, ab->get_alignments()[0].score, ab->get_alignments()[0].similarity_score, ab->get_alignments()[0].identity, ab->get_alignments()[0].similarity, -1, -1);
			}
		}
		else {
			ab->align(iquery_sequence.get_sequence(), idatabase_sequence.get_sequence(), iopt->get_gap_open(), iopt->get_gap_extension());
			search->save_reported_record(ab->get_alignments()[0].query_alignment, ab->get_alignments()[0].midline_alignment, idatabase_sequence.get_header(), ab->get_alignments()[0].hit_alignment, ab->get_alignments()[0].score, ab->get_alignments()[0].similarity_score, ab->get_alignments()[0].identity, ab->get_alignments()[0].similarity, -1, -1);
		}

	}
	catch (std::invalid_argument &e) {
		WARNING(e.what());
	}

	return 0;
}


void NscSearch::save_reported_record(std::string iquery, std::string imidline, std::string ihit_header,
		std::string ihit_sequence, float score, float simi_score, float identity, float similarity, int fragment_begin,
		int fragment_end) {
	if (score < opt->get_threshold()) {
		return;
	}

	results_item_t item;
	item.query_alignment = iquery;
	item.midline_alignment = imidline;
	item.hit_alignment = ihit_sequence;

	item.hit_header = ihit_header;

	item.score = score;
	item.simi_score = simi_score;
	item.similarity = similarity;
	item.identity = identity;

	item.fragment_info.begin = fragment_begin;
	item.fragment_info.end = fragment_end;

	std::lock_guard<std::mutex> guard(results_append_mutex);
	results.alignments.push_back(item);
}


float get_max_similarity_score(Options *opt, AlignBase *ab, string isequence) {
	ab->align(isequence, isequence, opt->get_gap_open(), opt->get_gap_extension());
	return ab->get_alignments()[0].score;
}


vector<AlignBase*> setup_alignment_algorithms(Options *opt, Sequence &iquery_sequence) {
	int thread_count = opt->get_thread_count();
	assert(thread_count > 0);

	vector<AlignBase*> abs;
	for (size_t i=0; i<thread_count; i++) {
		if (opt->get_align_algorithm() == AlignAlgorithm::GLOBAL) {
			abs.push_back(new NeedlemanWunsch());
		}
		else if (opt->get_align_algorithm() == AlignAlgorithm::ONE_WAY_GLOBAL) {
			abs.push_back(new OneWayGlobal());
		}
		else if (opt->get_align_algorithm() == AlignAlgorithm::LOCAL) {
			abs.push_back(new SmithWaterman());
		}
		else {
			NotImplemented(__FILE__, __LINE__);
		}
	}

	for (AlignBase* ab : abs) {
		if (opt->get_unmasked_residues().length() != 0) {
			std::string residues = opt->get_unmasked_residues();
			ab->mask_residues_except_selected_diagonal(std::vector<char>(residues.begin(), residues.end()));
		}
		else if (opt->get_alpha_of_cbr_correction() >= 0) {
			ab->set_cbr_correction(iquery_sequence.get_sequence(), opt->get_alpha_of_cbr_correction());
		}
	}

	float max_sim_score = 0;
	if (iquery_sequence.get_sequence().compare("") != 0) {
		max_sim_score = get_max_similarity_score(opt, (abs[0]), iquery_sequence.get_sequence());
	}

	for (AlignBase* ab : abs) {
		ab->set_max_score(max_sim_score);
	}

	return abs;
}

void delete_alignment_algorithms(Options *opt, vector<AlignBase*> abs) {
	for (AlignBase* ab : abs) {
		delete ab;
	}
}


results_t NscSearch::scan_database(Sequence &iquery_sequence) {
	assert(database_reader != nullptr);  // You have to call different constructor

	int thread_count = opt->get_thread_count();

	ThreadPool thread_pool(thread_count);

	if (thread_count < 2) {
		thread_count = 1;
	}

	vector<AlignBase*> abs = setup_alignment_algorithms(opt, iquery_sequence);
	KmerFilter kmer_filter;
	kmer_filter.set_acceptance_threshold(opt->get_kmer_filter_threshold());
	kmer_filter.initialize_query_sequnce(iquery_sequence.get_sequence());

	const int NUMBER_OF_THREADS_IN_WAITING_QUEUE = 20;
	while (database_reader->has_next_sequence()) {
		while (thread_pool.get_tasks_count() > (NUMBER_OF_THREADS_IN_WAITING_QUEUE * thread_count)) std::this_thread::sleep_for(std::chrono::microseconds(500));
		Sequence ds = database_reader->get_next_sequence();
		if (ds.get_sequence().length() == 0) {
			continue;
		}

		float longer_length = max(iquery_sequence.get_sequence().length(), ds.get_sequence().length());
		float shorter_length = min(iquery_sequence.get_sequence().length(), ds.get_sequence().length());
//		if ((shorter_length != 0) && ((longer_length / shorter_length) < 2)) {
//			if (nscsearch::jaccard_index(iquery_sequence.get_sequence_ptr(), ds.get_sequence_ptr()) > 0.5) {
				if (thread_count > 1) {
					std::future<int> x = thread_pool.enqueue(scan_fasta_thread, thread_pool.get_worker_ids(), this, iquery_sequence, ds, opt, &abs, &kmer_filter);//, opt->get_gap_open(), opt->get_gap_extension());
				} else {
					scan_fasta_thread(nullptr, this, iquery_sequence, ds, opt, &abs, &kmer_filter); //, opt->get_gap_open(), opt->get_gap_extension());
				}
//			}
//		}
	}

	while (thread_pool.get_tasks_count() > 0) std::this_thread::sleep_for(std::chrono::microseconds(500));

	thread_pool.dispose();

	delete_alignment_algorithms(opt, abs);

	return results;
}



