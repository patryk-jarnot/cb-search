/*
 * kmer.cpp
 *
 *  Created on: Jun 24, 2025
 *      Author: pjarnot
 */

#include "filters/kmer.hpp"

#include "debug.hpp"

#include <cstring>


using namespace std;
using namespace nscsearch;





bool KmerFilter::process_window(std::string ifirst_window) {
	if (ifirst_window.empty()) {
		return false;
	}

	char prev_char = ifirst_window[0] - 'A';
	prev_n_term_residue = prev_char;
	for (size_t i=1; i<ifirst_window.size(); i++) {
		char c = ifirst_window[i] - 'A';
		if (hit_count_by_kmer[prev_char][c] < query_count_by_kmer[prev_char][c]) {
			similar_kmers++;
			if ((float)similar_kmers/window_length >= acceptance_threshold) {
				return true;
			}
		}
		hit_count_by_kmer[prev_char][c]++;
		prev_char = c;
	}
	prev_c_term_residue = prev_char;
	return false;
}


bool KmerFilter::change_terminus_residues(char in_term_residue, char ic_term_residue) {
	in_term_residue -= 'A';
	ic_term_residue -= 'A';

	if (hit_count_by_kmer[prev_n_term_residue][in_term_residue] > 0) {
		if (query_count_by_kmer[prev_n_term_residue][in_term_residue] >= hit_count_by_kmer[prev_n_term_residue][in_term_residue]) {
			similar_kmers--;
		}
	}
	hit_count_by_kmer[prev_n_term_residue][in_term_residue]--;

	if (hit_count_by_kmer[prev_c_term_residue][ic_term_residue] < query_count_by_kmer[prev_c_term_residue][ic_term_residue]) {
		similar_kmers++;
		if ((float)similar_kmers/window_length >= acceptance_threshold) {
			return true;
		}
	}
	hit_count_by_kmer[prev_c_term_residue][ic_term_residue]++;

	prev_n_term_residue = in_term_residue;
	prev_c_term_residue = ic_term_residue;

	return false;

}


void KmerFilter::initialize_query_sequnce(std::string iquery) {
	if (iquery.empty()) {
		return;
	}
	window_length = iquery.size();
	similar_kmers = 0;
	char prev_char = iquery[0] - 'A';
	for (size_t i=1; i<iquery.size(); i++) {
		char c = iquery[i] - 'A';
		query_count_by_kmer[prev_char][c]++;
		prev_char = c;
	}
}


bool KmerFilter::contain_similar_fragment(std::string ihit) {
	memset(hit_count_by_kmer, 0, sizeof(hit_count_by_kmer[0][0]) * KMER_ARRAY_SIZE * KMER_ARRAY_SIZE);
	similar_kmers = 0;

	if (window_length > ihit.size()) {
		return process_window(ihit);
	}

	if ( true == process_window(ihit.substr(0, window_length)) ) {
		return true;
	}
	for (size_t i=1; i<(ihit.size() - window_length + 1); i++) {
//		DEBUG("3, i+iquery.size()-1: " << i+iquery.size()-1 << ", ihit.size(): " << ihit.size() << ", similarity: " << (float)similar_kmers/window_length);
		if ( true == change_terminus_residues(ihit[i], ihit[i+window_length-1]) ) {
			return true;
		}
	}
	return false;
}

bool KmerFilter::contain_similar_fragment(std::string iquery, std::string ihit, float iacceptance_threshold) {
	set_acceptance_threshold(iacceptance_threshold);
	initialize_query_sequnce(iquery);
	return contain_similar_fragment(ihit);
}

