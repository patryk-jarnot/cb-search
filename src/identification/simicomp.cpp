/*
 * simicomp.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: pjarnot
 */



#include "identification/simicomp.hpp"
#include "utils/functionutils.hpp"
#include "utils/numericutils.hpp"

#include "debug.hpp"

#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>
#include <limits>
#include <chrono>
#include <cassert>
#include <cmath>
#include <map>

using namespace std;
using namespace std::chrono;
using namespace nscsearch;

#define ALPHABET_SIZE 21


void calculate_window_composition(int *window_composition, std::vector<char> *isequence, int begin, int size) {
	int len = min((int)isequence->size()-begin, size);
	for (int i=0; i<len; i++) {
		window_composition[(*isequence)[i+begin]]++;
	}
}


int calculate_score(int *query_composition, int *hit_window_composition, int size) {
	int score = 0;
	for (int i=0; i<size; i++) {
		score += min(query_composition[i], hit_window_composition[i]);
	}
	return score;
}

float calculate_normalized_score(int *query_composition, int *hit_window_composition, int size, int query_size, int window_size) {
	float score = 0;
	for (int i=0; i<size; i++) {
//		score += min((float)query_composition[i], (float)hit_window_composition[i]);
		score += min((float)query_composition[i]/query_size, (float)hit_window_composition[i]/window_size);
	}
//	return score/window_size;
	return score;
}

void modify_window_composition_and_score(int *query_composition, int *hit_window_composition, int &score, char left_residue, char approached_residue, int query_len, int window_len) {
	hit_window_composition[left_residue]--;
	if ( number_lower( ((float)hit_window_composition[left_residue]/window_len), ((float)query_composition[left_residue]/query_len) ) ) {
		score--;
	}
	hit_window_composition[approached_residue]++;
	if ( number_lower_equal( ((float)hit_window_composition[approached_residue]/window_len), ((float)query_composition[approached_residue]/query_len) ) ) {
		score++;
	}
}

void modify_window_composition_and_score_normalized(int *query_composition, int *hit_window_composition, float &score, char left_residue, char approached_residue, int query_size, int window_size) {
	score -= min((float)query_composition[left_residue]/query_size, (float)hit_window_composition[left_residue]/window_size);
	hit_window_composition[left_residue]--;
	score += min((float)query_composition[left_residue]/query_size, (float)hit_window_composition[left_residue]/window_size);
//	if ( number_lower( ((float)hit_window_composition[left_residue]/window_len), ((float)query_composition[left_residue]/query_len) ) ) {
//		score -= (float)1/window_len;
//	}
	score -= min((float)query_composition[approached_residue]/query_size, (float)hit_window_composition[approached_residue]/window_size);
	hit_window_composition[approached_residue]++;
	score += min((float)query_composition[approached_residue]/query_size, (float)hit_window_composition[approached_residue]/window_size);
//	if ( number_lower_equal( ((float)hit_window_composition[approached_residue]/window_len), ((float)query_composition[approached_residue]/query_len) ) ) {
//		score += (float)1/window_len;
//	}
}


void SimiComp::similarity_score_per_window(std::vector<float> &oscores, std::vector<char> &iquery, std::vector<char> &ihit) {
	int window_size = iquery.size();

	oscores.resize(max(1, (int)ihit.size()-window_size+1));

	int query_composition[ALPHABET_SIZE];
	memset(query_composition, 0, sizeof(query_composition));
	calculate_window_composition(query_composition, &iquery, 0, window_size);

	int hit_window_len = min((int)ihit.size(), window_size);
	int hit_window_composition[ALPHABET_SIZE];
	memset(hit_window_composition, 0, sizeof(hit_window_composition));
	calculate_window_composition(hit_window_composition, &ihit, 0, hit_window_len);

	int score = calculate_score(query_composition, hit_window_composition, ALPHABET_SIZE);
	oscores[0] = (float)score / window_size;

#warning MAYBE IT SHOULD START WITH int i=1?
	for (int i=1; i<(int)ihit.size()-window_size+1; i++) {
		modify_window_composition_and_score(query_composition, hit_window_composition, score, ihit[i-1], ihit[i+window_size-1], window_size, window_size);
		oscores[i] = (float)score / window_size;
	}
}


void SimiComp::encode_string(std::string &iraw_string, std::vector<char> &oencoded_string) {
	for (int i=0; i<iraw_string.size(); i++) {
		oencoded_string[i] = mapper[iraw_string[i]];
	}
}


void find_extremas(vector<identification_result_t> &oretval, vector<float> &isimilarity_scores, int iwindow_size, float ifrequency_diff_threshold) {
	vector<int> indexes;

//	int min_score = ifrequency_diff_threshold * iwindow_size;
	bool in_region = false;
	int current_max_idx = -1;
	float current_max = -1;
	for (auto it=isimilarity_scores.begin(); it!= isimilarity_scores.end(); it++) {
		if ((float)*it > ifrequency_diff_threshold) {
			if ((*it > current_max)) {
				current_max_idx = distance(isimilarity_scores.begin(), it);
				current_max = *it;
				in_region = true;
			}
		}
		else {
			if (in_region) {
				indexes.push_back(current_max_idx);
				current_max_idx = -1;
				current_max = -1;
				in_region = false;
			}
		}
	}
	if (in_region) {
		indexes.push_back(current_max_idx);
		current_max_idx = -1;
		current_max = -1;
		in_region = false;
	}

	for (auto it=indexes.begin(); it!=indexes.end(); it++) {
		oretval.push_back(identification_result_t(*it+1, *it+iwindow_size));
	}
}

bool compare_identification_results(const identification_result_t &left, const identification_result_t &right) {
	return left.score < right.score;
}


void copy_scores(vector<identification_result_t> *max_scores, vector<float> *smoothed_max_scores) {
	for (int i=0; i<max_scores->size(); i++) {
		(*smoothed_max_scores)[i] = (*max_scores)[i].score;
	}
}


identification_result_t find_best_window(vector<identification_result_t> *max_scores, float ifrequency_diff_threshold, float irelative_threshold) {
	float prev_smoothed_score = 0;
	float prev_score = 0;
	identification_result_t best;

	vector<float> smoothed_max_scores(max_scores->size());
	copy_scores(max_scores, &smoothed_max_scores);
	int imoving_average_history = 2;
	smoothed_max_scores = nscsearch::moving_average(smoothed_max_scores, imoving_average_history);

	float max_score = (*std::max_element((*max_scores).begin(), (*max_scores).end(), compare_identification_results)).score;
	float relative_threshold = max_score - irelative_threshold;

	for (int i=0; i<max_scores->size(); i++) {
		if ((*max_scores)[i].score > relative_threshold && smoothed_max_scores[i] >= prev_smoothed_score && (*max_scores)[i].score >= prev_score) {
			best = (*max_scores)[i];
		}
//		DEBUG(" prev_score: " << prev_score << " score: " << (*max_scores)[i].score << " prev_smoothed_score: " << prev_smoothed_score << " smoothed_max_scores[i]: " << smoothed_max_scores[i] << " begin: " << (*max_scores)[i].begin << " end: " << (*max_scores)[i].end);
		prev_smoothed_score = smoothed_max_scores[i];
		prev_score = (*max_scores)[i].score;
	}
	best.begin = best.begin + 1;
	return best;
}


void adjust_regions_lengths(vector<identification_result_t> &ioregions, std::vector<char> *iquery, std::vector<char> *ihit, int iinitial_window_length, float ifrequency_diff_threshold, float irelative_threshold) {
	int min_window_length = round((float)iinitial_window_length / 2);
	int max_window_length = iinitial_window_length * 2;

	int query_composition[ALPHABET_SIZE];
	memset(query_composition, 0, sizeof(query_composition));
	calculate_window_composition(query_composition, iquery, 0, iquery->size());

	for (int i=0; i<ioregions.size(); i++) {
		std::vector<identification_result_t> max_scores;
		for (int wl=min_window_length; wl<=max_window_length; wl++) {
//			DEBUG("wl: " << wl << ", iinitial_window_length: " << iinitial_window_length);
			// TODO: Determine length of scores vector.
			std::vector<identification_result_t> scores;
			int scan_begin = max(min(ioregions[i].begin-1, ioregions[i].end - wl), 0);
//			int scan_end = min(max(ioregions[i].end, ioregions[i].begin-1 + wl), (int)(*ihit).size()-1);
			int scan_end = min(max(ioregions[i].end, ioregions[i].begin-1 + wl), ((int)((*ihit).size()))-1);

			int window_composition[ALPHABET_SIZE];
			memset(window_composition, 0, sizeof(window_composition));
			calculate_window_composition(window_composition, ihit, scan_begin, wl);
			float score = calculate_normalized_score(query_composition, window_composition, ALPHABET_SIZE, iquery->size(), wl);
			scores.push_back(identification_result_t(scan_begin, scan_begin+wl, (float)score));
//			DEBUG("n.score: " << (float)score << ", begin: " << scan_begin << ", end: " << scan_begin + wl << ", wl: " << wl << ", (scan_end-wl): " << (scan_end-wl));

			for (int pos=scan_begin+1; pos<=(scan_end-wl+1); pos++) {
				modify_window_composition_and_score_normalized(query_composition, window_composition, score, (*ihit)[pos-1], (*ihit)[pos+wl-1], iquery->size(), wl);
				scores.push_back(identification_result_t(pos, pos+wl, (float)score));
//				DEBUG("n.score: " << (float)score << ", begin: " << pos << ", end: " << pos + wl << ", wl: " << wl << ", (scan_end-wl): " << (scan_end-wl));
			}
			max_scores.push_back(*std::max_element(scores.begin(), scores.end(), compare_identification_results));
//			DEBUG("max_score: " << (max_scores.end()-1)->score);
//			DEBUG("");
		}
		ioregions[i] = find_best_window(&max_scores, ifrequency_diff_threshold, irelative_threshold);
	}
}


std::vector<identification_result_t> SimiComp::identify(std::string &iquery, std::string &ihit,
		float ifrequency_diff_threshold, float irelative_threshold) {

//	auto start = high_resolution_clock::now();
//	if (ihit.size() < iquery.size()) {
//		cerr << "Hit shorter than window size...\n";
//		return vector<identification_result_t>();
//	}
	std::vector<char> query_encoded(iquery.size());
	std::vector<char> hit_encoded(ihit.size());

	encode_string(iquery, query_encoded);
	encode_string(ihit, hit_encoded);
	vector<float> similarity_scores;
	similarity_score_per_window(similarity_scores, query_encoded, hit_encoded);

//	cout << "\nSIMILARITY SCORES: \n";
//	for (auto it=similarity_scores.begin(); it!=similarity_scores.end(); it++) {
//		cout << *it << ",";
//	}
//	cout << "\n\n";

	vector<identification_result_t> retval;

	int extremas_window_size = min(iquery.size(), ihit.size());
	find_extremas(retval, similarity_scores, extremas_window_size, ifrequency_diff_threshold);

//	auto p0 = high_resolution_clock::now();

	adjust_regions_lengths(retval, &query_encoded, &hit_encoded, query_encoded.size(), ifrequency_diff_threshold, irelative_threshold);

//	auto duration_p0 = duration_cast<microseconds>(p0 - start);
//	cout << "duration_p0: " << duration_p0.count() << "\n";

	return retval;
}


bool SimiComp::contain_similar_fragment(std::string &iquery, std::string &ihit, float ifrequency_diff_threshold) {
	std::vector<char> query_encoded(iquery.size());
	std::vector<char> hit_encoded(ihit.size());

	encode_string(iquery, query_encoded);
	encode_string(ihit, hit_encoded);

	int window_size = iquery.size();

	if (ihit.size()<window_size) {
//		cerr << "Hit shorter than window size. Query: " << iquery << ", hit: " << ihit << "\n";
		return false;
	}

	int query_composition[ALPHABET_SIZE];
	memset(query_composition, 0, sizeof(query_composition));
	calculate_window_composition(query_composition, &query_encoded, 0, window_size);

	int hit_window_len = min((int)ihit.size(), window_size);
	int hit_window_composition[ALPHABET_SIZE];
	memset(hit_window_composition, 0, sizeof(hit_window_composition));
	calculate_window_composition(hit_window_composition, &hit_encoded, 0, hit_window_len);

	int score = calculate_score(query_composition, hit_window_composition, ALPHABET_SIZE);
	float norm_score = (float)score / hit_window_len;
	if (norm_score >= ifrequency_diff_threshold) {
		return true;
	}

	for (int i=1; i<(int)ihit.size()-window_size+1; i++) {
		modify_window_composition_and_score(query_composition, hit_window_composition, score, hit_encoded[i-1], hit_encoded[i+window_size-1], window_size, window_size);
		norm_score = (float)score / window_size;
		if (norm_score >= ifrequency_diff_threshold) {
			return true;
		}
	}
	return false;
}


SimiComp::SimiComp() {
	mapper['A'] = 1;
	mapper['C'] = 2;
	mapper['D'] = 3;
	mapper['E'] = 4;
	mapper['F'] = 5;
	mapper['G'] = 6;
	mapper['H'] = 7;
	mapper['I'] = 8;
	mapper['K'] = 9;
	mapper['L'] = 10;
	mapper['M'] = 11;
	mapper['N'] = 12;
	mapper['P'] = 13;
	mapper['Q'] = 14;
	mapper['R'] = 15;
	mapper['S'] = 16;
	mapper['T'] = 17;
	mapper['V'] = 18;
	mapper['W'] = 19;
	mapper['Y'] = 20;
}

