/*
 * testkmer.cpp
 *
 *  Created on: Jun 24, 2025
 *      Author: pjarnot
 */



#include "tests/unittest.hpp"

#include "debug.hpp"

#include "filters/kmer.hpp"
#include "tests/filters/testkmer.hpp"

using namespace std;
using namespace nscsearch;


void test_filter_kmer_window_allow() {
	string query_sequence = "AAAAAAAAAA";
	string hit_sequence = "AAAAAAAAAA";
	KmerFilter filter;
	filter.initialize_query_sequnce(query_sequence);

	ASSERT(filter.process_window(hit_sequence) == true);
}


void test_filter_kmer_window_reject() {
	string query_sequence = "AAAAAAAAAA";
	string hit_sequence = "CCCCCCCCCC";
	KmerFilter filter;
	filter.initialize_query_sequnce(query_sequence);

	ASSERT(filter.process_window(hit_sequence) == false);
}


void test_filter_kmer_move_window_allow() {
	string query_sequence = "AAAAAAAAAA";
	string hit_sequence = "CCCCCCCCCC";
	KmerFilter filter;
	filter.set_acceptance_threshold(0.5);
	filter.initialize_query_sequnce(query_sequence);

	filter.process_window(hit_sequence);
	filter.change_terminus_residues('C', 'A');
	filter.change_terminus_residues('C', 'A');
	filter.change_terminus_residues('C', 'A');
	filter.change_terminus_residues('C', 'A');
	filter.change_terminus_residues('C', 'A');

	ASSERT(filter.change_terminus_residues('C', 'A') == true);
}


void test_filter_kmer_move_window_reject() {
	string query_sequence = "AAAAAAAAAA";
	string hit_sequence = "CCCCCCCCCC";
	KmerFilter filter;
	filter.set_acceptance_threshold(0.5);
	filter.initialize_query_sequnce(query_sequence);

	filter.process_window(hit_sequence);
	filter.change_terminus_residues('C', 'D');
	filter.change_terminus_residues('C', 'D');
	filter.change_terminus_residues('C', 'D');
	filter.change_terminus_residues('C', 'D');
	filter.change_terminus_residues('C', 'D');

	ASSERT(filter.change_terminus_residues('C', 'D') == false);
}

void test_filter_kmer_scan_sequence_identical_motif() {
	string query = "RGGFRGRGGFRGGFRGGFRGGFSRGGFGGPRGGFGGPRGGYGGYSRGGYGGYSRGGYGGSRGGYDSPRGGYDSPRGGYSRGGYGGPRNDYGPPRGSYGGSRGGYDGPRGDYG";
	string hit = "MSEAQETHVEQLPESVVDAPVEEQHQEPPQAPDAPQEPQVPQESAPQESAPQEPPAPQEQNDVPPPSNAPIYEGEESHSVQDYQEAHQHHQPPEPQPYYPPPPPGEHMHGRPPMHHRQEGELSNTRLFVRPFPLDVQESELNEIFGPFGPMKEVKILNGFAFVEFEEAESAAKAIEEVHGKSFANQPLEVVYSKLPAKRYRITMKNLPEGCSWQDLKDLARENSLETTFSSVNTRDFDGTGALEFPSEEILVEALERLNNIEFRGSVITVERDDNPPPIRRSNRGGFRGRGGFRGGFRGGFRGGFSRGGFGGPRGGFGGPRGGYGGYSRGGYGGYSRGGYGGSRGGYDSPRGGYDSPRGGYSRGGYGGPRNDYGPPRGSYGGSRGGYDGPRGDYGPPRDAYRTRDAPRERSPTR";

	KmerFilter filter;

	ASSERT(filter.contain_similar_fragment(query, hit, 0.9) == true);
}


void TestKmerFilter::run() {
	test_filter_kmer_scan_sequence_identical_motif();
	test_filter_kmer_window_allow();
	test_filter_kmer_window_reject();
	test_filter_kmer_move_window_allow();
	test_filter_kmer_move_window_reject();


	std::cerr << "\n";
}





