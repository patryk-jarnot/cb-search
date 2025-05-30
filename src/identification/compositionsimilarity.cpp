/*
 * complexitysimilarity.cpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */

#include "debug.hpp"

#include <vector>
#include <cassert>
#include "identification/compositionmatrix.hpp"
#include "identification/compositionsimilarity.hpp"

using namespace std;

namespace nscsearch {

//	void handle_gap_open(matrix_cell_t &iresidue, float *ioscore, float igap_open) {
//		if (iresidue.residue_query != '-' && iresidue.residue_hit != '-') {
//			*ioscore -= igap_open * 2;
//		}
//		else {
//			*ioscore -= igap_open;
//		}
//	}
//
//	void handle_gap_extend(matrix_cell_t &iresidue_pair, float *ioscore, float igap_extend) {
//		if (iresidue_pair.residue_query != '-' && iresidue_pair.residue_hit != '-') {
//			*ioscore -= iresidue_pair.count * igap_extend * 2;
//		}
//		else {
//			*ioscore -= iresidue_pair.count * igap_extend;
//		}
//	}
//
//	bool is_residue_without_pair(matrix_cell_t &iresidue_pair) {
//		return iresidue_pair.residue_query == '-' || iresidue_pair.residue_hit == '-';
//	}

//	void calculate_score_for_missing_hit_residue(bool *iois_gap_opened_with_gap, bool *iois_gap_opened, matrix_cell_t &residue_pair,
//				float *score_with_gap, float *score, float igap_open, float igap_extend) {
//		if ( false == *iois_gap_opened_with_gap ) {
//			handle_gap_open(residue_pair, score_with_gap, igap_open);
//			*iois_gap_opened_with_gap = true;
//		}
//		if ( false == *iois_gap_opened) {
//			handle_gap_open(residue_pair, score, igap_open);
//			*iois_gap_opened = true;
//		}
//		handle_gap_extend(residue_pair, score_with_gap, igap_extend);
//		handle_gap_extend(residue_pair, score, igap_extend);
//	}
//
//	void calculate_score_for_residue_with_pair(bool *iois_gap_opened_with_gap, bool *iois_gap_opened, matrix_cell_t &residue_pair,
//				float *score_with_gap, float *score, float igap_open, float igap_extend) {
//		*score += residue_pair.score * residue_pair.count;
//#warning if both residues are present then we do two gaps igap_open should be multiplied by 2. Here we handle case where one residue is present and the other is '-'. Write tests for this if statement
////		if ( residue_pair.score < igap_open ) {
//		if ( residue_pair.score < (igap_open*2) ) {
//			if ( false == *iois_gap_opened_with_gap ) {
//				handle_gap_open(residue_pair, score_with_gap, igap_open);
//				*iois_gap_opened_with_gap = true;
//			}
//			handle_gap_extend(residue_pair, score_with_gap, igap_extend);
//		}
//		else {
//			*score_with_gap += residue_pair.score * residue_pair.count;
//		}
//	}

//	float CompositionSimilarity::calculate_maximal_similarity(std::string isequence_query,
//			std::string isequence_hit, ScoringMatrix *ism, float igap_open, float igap_extend) {
//		CompositionMatrix cm;
//		cm.generate_matrix(isequence_query, isequence_hit);
//		matrix_cell_t residue_pair;
//		float score = 0;
//		float score_with_gap = 0;
//
//		bool is_gap_opened = false;
//		bool is_gap_opened_with_gap = false;
//
//		while ( cm.pop_residue_pair_with_highest_score(&residue_pair) ) {
//			if ( is_residue_without_pair(residue_pair) ) {
//				calculate_score_for_missing_hit_residue(&is_gap_opened_with_gap, &is_gap_opened, residue_pair, &score_with_gap, &score, igap_open, igap_extend);
//			}
//			else {
//				calculate_score_for_residue_with_pair(&is_gap_opened_with_gap, &is_gap_opened, residue_pair, &score_with_gap, &score, igap_open, igap_extend);
//			}
//		}
//
//		return std::max(score, score_with_gap);
//	}

	void CompositionSimilarity::precalculations() {
		complexity_matrix.precalculations();
	}

	void CompositionSimilarity::initialize_calculator(std::string isequence_query, std::string isequence_hit,
			ScoringMatrix *ism) {
		complexity_matrix.initialize_matrix(isequence_query, isequence_hit);
	}

	float CompositionSimilarity::calculate_maximal_similarity() {
		vector<matrix_pair_t> residue_pairs = complexity_matrix.get_matrix_pairs_ordered_by_score_desc();

		float score = 0;

		complexity_matrix.restore_tmp_vectors();
		for (auto pair : residue_pairs) {
			int count = complexity_matrix.pop_pair_count(pair.residue_query, pair.residue_hit);
			score += count * pair.score;
		}

		return score;
	}

	void CompositionSimilarity::replace_hit_residue(char iold_residue, char inew_residue) {
		complexity_matrix.replace_hit_residue(residue_to_matrix_index(iold_residue), residue_to_matrix_index(inew_residue));
	}
}


