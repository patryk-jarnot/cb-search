/*
 * complexitymatrix.cpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */


#include "model/matrixresidue.hpp"

#include "constants.hpp"

#include "debug.hpp"

#include <limits>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include "identification/compositioncalculator.hpp"
#include "identification/compositionmatrix.hpp"

using namespace std;

namespace nscsearch {

	bool matrix_pair_comparator(const matrix_pair_t& lhs, const matrix_pair_t& rhs) {
	   return lhs.score > rhs.score;
	}

	void CompositionMatrix::precalculations() {
		for (int i=0; i<(int)MatrixResidue::STAR; i++) {
			for (int j=0; j<(int)MatrixResidue::STAR; j++) {
				matrix_pair_t pair;
				pair.residue_query = (MatrixResidue)i;
				pair.residue_hit = (MatrixResidue)j;
				pair.score = scoring_matrix.get_score((MatrixResidue)i, (MatrixResidue)j);
				matrix_pairs_ordered_by_score_desc.push_back(pair);
			}
		}
		sort(matrix_pairs_ordered_by_score_desc.begin(), matrix_pairs_ordered_by_score_desc.end(), matrix_pair_comparator);
	}

	void CompositionMatrix::initialize_matrix(std::string sequence_query, std::string sequence_hit) {
		memset(composition_matrix, 0, sizeof(int) * SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE);

		CompositionCalculator cc;
		counts_in_query_sequence = cc.count_sequence_residues(sequence_query);
		counts_in_hit_sequence = cc.count_sequence_residues(sequence_hit);

		counts_in_query_sequence_tmp = counts_in_query_sequence;
		counts_in_hit_sequence_tmp = counts_in_hit_sequence;
	}


	int CompositionMatrix::get_pair_count(char ileft_residue, char iright_residue) {
		return get_pair_count(residue_to_matrix_index(ileft_residue), residue_to_matrix_index(iright_residue));
	}

	int CompositionMatrix::get_pair_count(MatrixResidue ileft_residue, MatrixResidue iright_residue) {
		return std::min(counts_in_query_sequence[(int)ileft_residue], counts_in_hit_sequence[(int)iright_residue]);
	}

	void CompositionMatrix::restore_tmp_vectors() {
		counts_in_query_sequence_tmp = counts_in_query_sequence;
		counts_in_hit_sequence_tmp = counts_in_hit_sequence;
	}

	void CompositionMatrix::replace_hit_residue(MatrixResidue iold_residue, MatrixResidue inew_residue) {
		counts_in_hit_sequence[(int)iold_residue]--;
		counts_in_hit_sequence[(int)inew_residue]++;
	}

	int CompositionMatrix::get_hit_residue_count(MatrixResidue iresidue) {
		return counts_in_hit_sequence[(int)iresidue];
	}

	int CompositionMatrix::pop_pair_count(MatrixResidue ileft_residue, MatrixResidue iright_residue) {
		int pair_count = std::min(counts_in_query_sequence_tmp[(int)ileft_residue], counts_in_hit_sequence_tmp[(int)iright_residue]);
		counts_in_query_sequence_tmp[(int)ileft_residue] -= pair_count;
		counts_in_hit_sequence_tmp[(int)iright_residue] -= pair_count;
		return pair_count;
	}

	void CompositionMatrix::print_composition_matrix() {
		printf("%5d", 0);
		for (int i=0; i<(int)MatrixResidue::STAR; i++) {
			printf("%5d", i);
		}

		std::cout << std::endl;

		for (int i=0; i<(int)MatrixResidue::STAR; i++) {
			printf("%5d", i);
			for (int j=0; j<(int)MatrixResidue::STAR; j++) {
				printf("%5d", (composition_matrix)[i * SCORING_MATRIX_SIZE + j]);
			}
			std::cout << std::endl;
		}
	}
}


