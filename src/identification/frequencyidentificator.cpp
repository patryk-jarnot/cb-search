/*
 * similarcomplexity.cpp
 *
 *  Created on: May 4, 2023
 *      Author: pjarnot
 */


#include "identification/compositioncalculator.hpp"
#include "identification/frequencyidentificator.hpp"
#include "identification/compositionsimilarity.hpp"
#include "identification/fragmentextender.hpp"
#include "residue/scoringmatrix.hpp"
#include "utils/functionutils.hpp"

#include "debug.hpp"

#include <algorithm>
#include <string>
#include <iostream>
#include <limits>
#include <chrono>
#include <cassert>
#include <cmath>
#include <map>

using namespace std;
using namespace std::chrono;
using namespace nscsearch;



inline float calculate_frequency_similarity(size_t total_query_residue_count, size_t total_hit_residue_count, std::map<char, int> *count_by_query_residues, std::map<char, int> *count_by_hit_residues) {
	float similarities = 0;
	for (auto it=count_by_query_residues->begin(); it!=count_by_query_residues->end(); it++) {
		similarities += std::min((float)(*count_by_query_residues)[it->first]/total_query_residue_count, (float)(*count_by_hit_residues)[it->first]/total_hit_residue_count);
	}
	return similarities;
}

//inline float calculate_frequency_similarity_using_precalculations(size_t total_query_residue_count, size_t total_hit_residue_count, std::map<char, float> &frequency_by_query_residues, std::map<char, float> &frequency_by_hit_residues) {
//	float similarities = 0;
//	for (auto it=frequency_by_query_residues.begin(); it!=frequency_by_query_residues.end(); it++) {
//		similarities += std::min(it->second, frequency_by_hit_residues[it->first]);
//	}
//	return similarities;
//}

inline float calculate_frequency_similarity_using_precalculations(size_t total_query_residue_count, size_t total_hit_residue_count, std::map<char, float> &frequency_by_query_residues, std::map<char, int> &count_by_hit_residues) {
	float similarities = 0;
	for (auto it=frequency_by_query_residues.begin(); it!=frequency_by_query_residues.end(); it++) {
		similarities += std::min(it->second, (float)count_by_hit_residues[it->first]/total_hit_residue_count);
	}
	return similarities;
}

inline void calculate_frequency_from_counts(size_t itotal_query_residue_count, std::map<char, int> &icount_by_residues,
		std::map<char, float> *ifrequency_by_residues) {
	for (auto it=icount_by_residues.begin(); it!=icount_by_residues.end(); it++) {
		(*ifrequency_by_residues)[it->first] = (float)it->second / itotal_query_residue_count;
	}
}

inline void update_frequencies(size_t iwindow_size, char iamino_acid, int icount,
		std::map<char, float> *ifrequency_by_residues) {
	(*ifrequency_by_residues)[iamino_acid] = (float)icount / iwindow_size;
}

inline void initialize_count_vector(std::map<char, int> *icount_by_residues) {
	const int RESIDUE_COUNT = 25;
	char residues[RESIDUE_COUNT] = { 'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V', 'B', 'J', 'Z', 'X', '*' };

	for (int i=0; i<RESIDUE_COUNT; i++) {
		(*icount_by_residues)[residues[i]] = 0;
	}
}

vector<float> calculate_frequency_similarity_for_hit_over_query_window(std::string iquery, std::string ihit, float *max_frequency_similarity) {
		int windows_over_hit_count = ihit.size() - iquery.size() + 1;
		std::map<char, int> count_by_query_residues;
		std::map<char, int> count_by_hit_residues;

		std::map<char, float> frequency_by_query_residues;

		std::vector<float> frequency_similarity(windows_over_hit_count);
		size_t window_size = iquery.size();
		auto start = high_resolution_clock::now();

		initialize_count_vector(&count_by_query_residues);
		initialize_count_vector(&count_by_hit_residues);

		for (size_t i=0; i<iquery.size(); i++) {
			count_by_query_residues[iquery[i]]++;
			count_by_hit_residues[ihit[i]]++;
		}
		auto p0 = high_resolution_clock::now();

		calculate_frequency_from_counts(window_size, count_by_query_residues, &frequency_by_query_residues);
		frequency_similarity[0] = calculate_frequency_similarity_using_precalculations(window_size, window_size, frequency_by_query_residues, count_by_hit_residues);

		auto p1 = high_resolution_clock::now();
		for (size_t i=1; i<windows_over_hit_count; i++) {
			count_by_hit_residues[ihit[i+window_size-1]]++;
			count_by_hit_residues[ihit[i-1]]--;

			frequency_similarity[i] = calculate_frequency_similarity_using_precalculations(window_size, window_size, frequency_by_query_residues, count_by_hit_residues);
			if (frequency_similarity[i] > *max_frequency_similarity) {
				*max_frequency_similarity = frequency_similarity[i];
			}
		}
		auto p2 = high_resolution_clock::now();


		auto duration_p0 = duration_cast<microseconds>(p0 - start);
		auto duration_p1 = duration_cast<microseconds>(p1 - p0);
		auto duration_p2 = duration_cast<microseconds>(p2 - p1);

//		cout << "duration_freq_p0: " << duration_p0.count() << "\n";
//		cout << "duration_freq_p1: " << duration_p1.count() << "\n";
//		cout << "duration_freq_p2: " << duration_p2.count() << "\n";

		return frequency_similarity;
}

bool is_possible_fragment_start(int icurr_begin, float curr_frequency, float ifrequency_similarity_threshold) {
	return icurr_begin == 0 && curr_frequency > ifrequency_similarity_threshold;
}

bool is_started_and_higher_or_equal_frequency(int icurr_begin, float ibest_frequency, float icurrent_frequency) {
	return icurr_begin != 0 && ibest_frequency <= icurrent_frequency;
}

bool current_region_ended(int icurr_begin, float icurrent_frequency, float ifrequency_similarity_threshold) {
	return icurr_begin != 0 && ( icurrent_frequency < ifrequency_similarity_threshold );
}

bool is_end_scanning(int icurr_begin , size_t current_item_index, size_t last_item_index) {
	return icurr_begin != 0 && ( current_item_index == last_item_index );
}

vector<identification_result_t> find_fragments_of_most_similar_frequency(vector<float> *frequency_similarities, size_t iwindow_length, float ifrequency_similarity_threshold) {
	int current_max = -100000;
	vector<identification_result_t> retval;
	identification_result_t curr_max = identification_result_t();
	float best_frequency = 0;
	for (int i=0; i<frequency_similarities->size(); i++) {
		if (is_possible_fragment_start(curr_max.begin, (*frequency_similarities)[i], ifrequency_similarity_threshold)) {
			curr_max.begin = i+1;
			curr_max.end = i + iwindow_length;
			best_frequency = (*frequency_similarities)[i];
		}
		else if (is_started_and_higher_or_equal_frequency(curr_max.begin, best_frequency, (*frequency_similarities)[i])) {
			curr_max.begin = i+1;
			curr_max.end = i + iwindow_length;
			best_frequency = (*frequency_similarities)[i];
		}
		else if (current_region_ended(curr_max.begin, (*frequency_similarities)[i], ifrequency_similarity_threshold )) {
			retval.push_back(curr_max);
			curr_max.begin = 0;
			curr_max.end = 0;
		}
		if ( is_end_scanning(curr_max.begin, i, frequency_similarities->size() - 1) ) {
			retval.push_back(curr_max);
			curr_max.begin = 0;
			curr_max.end = 0;
		}
	}

	return retval;
}


void extend_left(string &ihit, std::map<char, int> &icount_by_query_residues,
		std::map<char, int> icount_by_hit_residues, int begin, int end,
		float ilow_threshold, float ihigh_threshold, int *oshrink_begin, float *oshrink_frequency) {
	int query_window_size = end - begin + 1;
	int cur_begin = begin;
	int cur_window_size = end - cur_begin + 1;
	float cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);
	float prev_frequency = 0;
	float prev_prev_frequency = 0;
	while (true) {
		cur_begin--;
		if (cur_begin <= 0) {
			break;
		}

		cur_window_size = end - cur_begin + 1;
		icount_by_hit_residues[ihit[cur_begin-1]]++;
		prev_prev_frequency = prev_frequency;
		if (cur_begin+2 == begin) {
			prev_prev_frequency = cur_frequency;
		}
		prev_frequency = cur_frequency;
		cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);

		if (cur_frequency < ilow_threshold) {
			break;
		}
		if (cur_frequency >= prev_frequency && prev_frequency >= prev_prev_frequency && cur_frequency > ihigh_threshold) {
			*oshrink_begin = cur_begin;
			*oshrink_frequency = cur_frequency;
		}
	}
}


void shrink_left(string &ihit, std::map<char, int> &icount_by_query_residues,
		std::map<char, int> icount_by_hit_residues, int begin, int end,
		float ilow_threshold, float ihigh_threshold, int *oshrink_begin, float *oshrink_frequency) {

	int query_window_size = end - begin + 1;
	int cur_begin = begin;
	int cur_window_size = end - cur_begin + 1;
	float cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);
	float initial_frequency = cur_frequency;
	float prev_frequency = cur_frequency;
	while (true) {
		cur_begin++;
		if (cur_begin >= end) {
			break;
		}

		cur_window_size = end - cur_begin + 1;
		icount_by_hit_residues[ihit[cur_begin-2]]--;
		prev_frequency = cur_frequency;
		cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);

		if (cur_frequency < ilow_threshold) {
			break;
		}
		if (cur_frequency > prev_frequency && cur_frequency > initial_frequency) {
			*oshrink_begin = cur_begin;
			*oshrink_frequency = cur_frequency;
		}
	}
}


void extend_right(size_t iquery_window, string &ihit, std::map<char, int> &icount_by_query_residues,
		std::map<char, int> icount_by_hit_residues, int begin, int end,
		float ilow_threshold, float ihigh_threshold, int *oshrink_end, float *oshrink_frequency) {
	int query_window_size = iquery_window;
	int cur_end = end;
	int new_end = cur_end;
	int cur_window_size = cur_end - begin + 1;
	float cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);
	float prev_frequency = 0;
	float prev_prev_frequency = 0;
	while (true) {
		cur_end++;
		if (cur_end >= ihit.size()) {
			break;
		}

		cur_window_size = cur_end - begin + 1;
		icount_by_hit_residues[ihit[cur_end-1]]++;

		prev_prev_frequency = prev_frequency;
		if (cur_end-2 == end) {
			prev_prev_frequency = cur_frequency;
		}
		prev_frequency = cur_frequency;
		cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);

		if (cur_frequency < ilow_threshold) {
			break;
		}
		if (cur_frequency >= prev_frequency && prev_frequency >= prev_prev_frequency && cur_frequency > ihigh_threshold) {
			*oshrink_end = cur_end;
			*oshrink_frequency = cur_frequency;
		}
	}
}

void shrink_right(size_t iquery_window, string &ihit, std::map<char, int> &icount_by_query_residues,
		std::map<char, int> icount_by_hit_residues, int begin, int end,
		float ilow_threshold, float ihigh_threshold, int *oshrink_end, float *oshrink_frequency) {

	int query_window_size = iquery_window;
	int cur_end = end;
	int cur_window_size = cur_end - begin + 1;
	float cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);
	float initial_frequency = cur_frequency;
	float prev_frequency = cur_frequency;
	float prev_prev_frequency = cur_frequency;
	while (true) {
		cur_end--;
		if (cur_end <= begin) {
			break;
		}

		cur_window_size = cur_end - begin + 1;
		icount_by_hit_residues[ihit[cur_end]]--;
		prev_prev_frequency = prev_frequency;
		prev_frequency = cur_frequency;
		cur_frequency = calculate_frequency_similarity(query_window_size, cur_window_size,
				&icount_by_query_residues, &icount_by_hit_residues);

		if (cur_frequency < prev_frequency && prev_frequency < prev_prev_frequency) {
			break;
		}

		if (cur_frequency < ilow_threshold) {
			break;
		}
		if (cur_frequency > prev_frequency && cur_frequency > initial_frequency) {
			*oshrink_end = cur_end;
			*oshrink_frequency = cur_frequency;
		}
	}
}


void shrink_and_extend_left(string &ihit, std::map<char, int> &icount_by_query_residues,
		std::map<char, int> &icount_by_hit_residues, identification_result_t *iolocations_of_similar_fragment,
		float ilow_threshold, float ihigh_threshold) {
	int shrink_begin = -1;
	float shrink_frequency = -1;
	shrink_left(ihit, icount_by_query_residues, icount_by_hit_residues, iolocations_of_similar_fragment->begin,
			iolocations_of_similar_fragment->end, ilow_threshold, ihigh_threshold, &shrink_begin, &shrink_frequency);

	int extend_begin = -1;
	float extend_frequency = -1;
	extend_left(ihit, icount_by_query_residues, icount_by_hit_residues, iolocations_of_similar_fragment->begin,
			iolocations_of_similar_fragment->end, ilow_threshold, ihigh_threshold, &extend_begin, &extend_frequency);

	if (extend_begin != -1) {// && extend_frequency >= shrink_frequency) {
		iolocations_of_similar_fragment->begin = extend_begin;
	}
	else if (shrink_begin != -1) {
		iolocations_of_similar_fragment->begin = shrink_begin;
	}
}


void shrink_and_extend_right(size_t iquery_window, string &ihit, std::map<char, int> &icount_by_query_residues,
		std::map<char, int> &icount_by_hit_residues, identification_result_t *iolocations_of_similar_fragment,
		float ilow_threshold, float ihigh_threshold) {

	int shrink_end = -1;
	float shrink_frequency = -1;
	shrink_right(iquery_window, ihit, icount_by_query_residues, icount_by_hit_residues, iolocations_of_similar_fragment->begin,
			iolocations_of_similar_fragment->end, ilow_threshold, ihigh_threshold, &shrink_end, &shrink_frequency);

	int extend_end = -1;
	float extend_frequency = -1;
	extend_right(iquery_window, ihit, icount_by_query_residues, icount_by_hit_residues, iolocations_of_similar_fragment->begin,
			iolocations_of_similar_fragment->end, ilow_threshold, ihigh_threshold, &extend_end, &extend_frequency);

	if (extend_end != -1) {// && extend_frequency >= shrink_frequency) {
		iolocations_of_similar_fragment->end = extend_end;
	}
	else if (shrink_end != -1) {
		iolocations_of_similar_fragment->end = shrink_end;
	}
}

void shrink_and_extend_fragment(string &iquery, string &ihit, identification_result_t *iolocations_of_similar_fragment,
		float ifrequency_diff_threshold) {
	std::map<char, int> count_by_query_residues;
	std::map<char, int> count_by_hit_residues;
	std::vector<float> frequency_similarity;

	CompositionCalculator cc;
	cc.initialize_count_vector(&count_by_query_residues);
	cc.initialize_count_vector(&count_by_hit_residues);

	for (size_t i=0; i<iquery.size(); i++) {
		count_by_query_residues[iquery[i]]++;
	}
	for (size_t i=iolocations_of_similar_fragment->begin-1; i<iolocations_of_similar_fragment->end; i++) {
		count_by_hit_residues[ihit[i]]++;
	}

	int cur_window_size = iolocations_of_similar_fragment->end - iolocations_of_similar_fragment->begin + 1;
	float cur_frequency = calculate_frequency_similarity(iquery.size(), cur_window_size, &count_by_query_residues, &count_by_hit_residues);
#warning make high_threshold from below parameter of the method.
	float high_threshold = cur_frequency - (float)3/iquery.size();
	float low_threshold = cur_frequency - (float)6/iquery.size();

	shrink_and_extend_left(ihit, count_by_query_residues, count_by_hit_residues, iolocations_of_similar_fragment,
			low_threshold, high_threshold);

	cc.initialize_count_vector(&count_by_hit_residues);
	for (size_t i=iolocations_of_similar_fragment->begin-1; i<iolocations_of_similar_fragment->end; i++) {
		count_by_hit_residues[ihit[i]]++;
	}

	shrink_and_extend_right(iquery.size(), ihit, count_by_query_residues, count_by_hit_residues, iolocations_of_similar_fragment,
			low_threshold, high_threshold);
}

void shrink_and_extend_similar_fragments(string &iquery, string &ihit, vector<identification_result_t> *iolocations_of_similar_frequency_fragments,
		float ifrequency_diff_threshold) {
	for (size_t i=0; i<iolocations_of_similar_frequency_fragments->size(); i++) {
		shrink_and_extend_fragment(iquery, ihit, &(*iolocations_of_similar_frequency_fragments)[i], ifrequency_diff_threshold);
	}
}

std::vector<identification_result_t> FrequencyIdentificator::identify(std::string iquery, std::string ihit,
		float ifrequency_diff_threshold) {
	if (iquery.size() > ihit.size()) {
		return vector<identification_result_t>();
	}
	auto start = high_resolution_clock::now();

	float max_frequency_similarity = 0;
	vector<float> frequency_similarities = calculate_frequency_similarity_for_hit_over_query_window(iquery, ihit, &max_frequency_similarity);
	if (max_frequency_similarity < ifrequency_diff_threshold) {
		return vector<identification_result_t>();
	}

	auto p0 = high_resolution_clock::now();

//	for (auto x : frequency_similarities) {
//		DEBUG(x)
//	}

	int imoving_average_window_span = 2;
	frequency_similarities = nscsearch::moving_average(frequency_similarities, imoving_average_window_span);

//	DEBUG("\n\n")
//
//	for (auto x : frequency_similarities) {
//		DEBUG(x)
//	}

	vector<identification_result_t> locations_of_similar_frequency_fragments = find_fragments_of_most_similar_frequency(&frequency_similarities, iquery.size(), ifrequency_diff_threshold);

	auto p1 = high_resolution_clock::now();

	shrink_and_extend_similar_fragments(iquery, ihit, &locations_of_similar_frequency_fragments, ifrequency_diff_threshold);

	auto p2 = high_resolution_clock::now();

	auto duration_p0 = duration_cast<microseconds>(p0 - start);
	auto duration_p1 = duration_cast<microseconds>(p1 - p0);
	auto duration_p2 = duration_cast<microseconds>(p2 - p1);

//	cout << "duration_p0: " << duration_p0.count() << "\n";
//	cout << "duration_p1: " << duration_p1.count() << "\n";
//	cout << "duration_p2: " << duration_p2.count() << "\n";

	return locations_of_similar_frequency_fragments;
}

