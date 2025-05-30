/*
 * sequencefrequency.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: pjarnot
 */



#include "identification/sequencefrequency.hpp"
#include "identification/compositioncalculator.hpp"

#include "debug.hpp"

#include <vector>

using namespace std;

namespace nscsearch {


	float calculate_frequency_similarity(size_t total_residue_count, std::map<char, int> *count_by_query_residues, std::map<char, int> *count_by_hit_residues) {
		int similarities = 0;
		for (auto it=count_by_query_residues->begin(); it!=count_by_query_residues->end(); it++) {
			similarities += std::min((*count_by_query_residues)[it->first], (*count_by_hit_residues)[it->first]);
		}
		return (float)similarities / total_residue_count;
	}

	vector<float> SequenceFrequency::calculate_frequency_similarity_for_hit_over_query_window(std::string iquery, std::string ihit) {
			std::map<char, int> count_by_query_residues;
			std::map<char, int> count_by_hit_residues;
			std::vector<float> frequency_similarity;

			CompositionCalculator cc;
			cc.initialize_count_vector(&count_by_query_residues);
			cc.initialize_count_vector(&count_by_hit_residues);

			for (size_t i=0; i<iquery.size(); i++) {
				count_by_query_residues[iquery[i]]++;
				count_by_hit_residues[ihit[i]]++;
			}

			frequency_similarity.push_back(calculate_frequency_similarity(iquery.size(), &count_by_query_residues, &count_by_hit_residues));
			int windows_over_hit_count = ihit.size() - iquery.size();
			for (size_t i=1; i<windows_over_hit_count; i++) {
				count_by_hit_residues[ihit[i+iquery.size()-1]]++;
				count_by_hit_residues[ihit[i-1]]--;
				frequency_similarity.push_back(calculate_frequency_similarity(iquery.size(), &count_by_query_residues, &count_by_hit_residues));
			}
//
//			for (auto x : frequency_similarity) {
//				DEBUG(x << " ")
//			}

			return frequency_similarity;
	}
}


