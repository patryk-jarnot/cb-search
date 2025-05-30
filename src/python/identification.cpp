/*
 * identification.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: pjarnot
 */


#include "python/identification.hpp"

#include "identification/simicomp.hpp"

#include <iostream>
#include <vector>

using namespace nscsearch;
using namespace std;


std::vector<float> window_similarity_scores(std::string iquery, std::string isequence) {
	vector<float> similarity_scores;
	SimiComp sc;
	if (isequence.size() < iquery.size()) {
//		cerr << "Hit shorter than window size...\n";
		return similarity_scores;
	}
	std::vector<char> query_encoded(iquery.size());
	std::vector<char> sequence_encoded(isequence.size());

	sc.encode_string(iquery, query_encoded);
	sc.encode_string(isequence, sequence_encoded);
	sc.similarity_score_per_window(similarity_scores, query_encoded, sequence_encoded);
	return similarity_scores;


//	return std::vector<float>();
}

std::vector<result_t> identify(std::string iquery, std::string isequence, float isimilarity_threshold) {
	SimiComp sc;

	std::vector<identification_result_t> results = sc.identify(iquery, isequence, isimilarity_threshold, 0.1);

	std::vector<result_t> results_result;

	for (auto item : results) {
		results_result.push_back(result_t{item.begin, item.end});
	}

	return results_result;
}

