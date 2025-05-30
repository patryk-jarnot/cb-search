/*
 * gapaffinitymatrix.cpp
 *
 *  Created on: Mar 27, 2023
 *      Author: pjarnot
 */

#include "alignment/nw/nwgapaffinitymatrices.hpp"
#include "exceptions.hpp"

#include "debug.hpp"
#include "assert.h"

#include <algorithm>

using namespace nscsearch;
using namespace std;



NwGapAffinityMatrices::NwGapAffinityMatrices() : sm(nullptr), gap_open(0), gap_extend(0) {

}


void NwGapAffinityMatrices::create_matrices(std::string sequence_upper,
		std::string sequence_lower, float gap_open, float gap_extend) {
	assert(sm != nullptr);

	this->sequence_upper = sequence_upper;
	this->sequence_lower = sequence_lower;
	this->gap_open = gap_open;
	this->gap_extend = gap_extend;



	matrix_m = std::vector<std::vector<float> >(sequence_lower.size()+1, std::vector<float>(sequence_upper.size()+1, FLOAT_MINUS_INF));
	matrix_m[0][0] = 0;
	matrix_ix = std::vector<std::vector<float> >(sequence_lower.size()+1, std::vector<float>(sequence_upper.size()+1, FLOAT_MINUS_INF));
	matrix_iy = std::vector<std::vector<float> >(sequence_lower.size()+1, std::vector<float>(sequence_upper.size()+1, FLOAT_MINUS_INF));

	fill_matrices();
}


void NwGapAffinityMatrices::fill_ix_first_row() {
	matrix_ix[0][1] = 0 - gap_open - gap_extend;
	for (size_t j=2; j<sequence_upper.size()+1; j++) {
		matrix_ix[0][j] = matrix_ix[0][j-1] - gap_extend;
	}
}


void NwGapAffinityMatrices::fill_iy_first_column() {
	matrix_iy[1][0] = 0 - gap_open - gap_extend;
	for (size_t i=2; i<sequence_lower.size()+1; i++) {
		matrix_iy[i][0] = matrix_iy[i-1][0] - gap_extend;
	}
}


void NwGapAffinityMatrices::fill_matrices_body() {
	for (size_t i=1; i<sequence_lower.length()+1; i++) {
		for (size_t j=1; j<sequence_upper.length()+1; j++) {
			int current_match_score = sm->get_score(sequence_lower[i-1], sequence_upper[j-1]);

//			cerr << "i: " << i << "; j: " << j << "; matrix_m[i-1][j-1]: " << matrix_m[i-1][j-1] << "; current_match_score: " << current_match_score << "; sequence_lower[i-1]: " << sequence_lower[i-1] << "; sequence_upper[j-1]: " << sequence_upper[j-1] << "\n";

			matrix_m[i][j] = std::max({ matrix_m[i-1][j-1] + current_match_score,
										matrix_ix[i-1][j-1] + current_match_score,
										matrix_iy[i-1][j-1] + current_match_score });

			matrix_ix[i][j] = std::max({ matrix_m[i][j-1] - gap_open - gap_extend,
										 matrix_ix[i][j-1] - gap_extend,
										 matrix_iy[i][j-1] - gap_open - gap_extend});

			matrix_iy[i][j] = std::max({ matrix_m[i-1][j] - gap_open - gap_extend,
										 matrix_ix[i-1][j] - gap_open - gap_extend,
										 matrix_iy[i-1][j] - gap_extend });
		}
	}
}


void NwGapAffinityMatrices::fill_matrices() {
	fill_iy_first_column();
	fill_ix_first_row();
	fill_matrices_body();
}


float NwGapAffinityMatrices::get_m_value(int i, int j) {
	return matrix_m[i][j];
}


float NwGapAffinityMatrices::get_ix_value(int i, int j) {
	return matrix_ix[i][j];
}


float NwGapAffinityMatrices::get_iy_value(int i, int j) {
	return matrix_iy[i][j];
}


void NwGapAffinityMatrices::print_matrix_m() {
	std::cout << std::endl << "Matrix M" << std::endl;
	print_matrix(&matrix_m);
}


void NwGapAffinityMatrices::print_matrix_ix() {
	std::cout << std::endl << "Matrix X" << std::endl;
	print_matrix(&matrix_ix);
}


void NwGapAffinityMatrices::print_matrix_iy() {
	std::cout << std::endl << "Matrix Y" << std::endl;
	print_matrix(&matrix_iy);
}

NwGapAffinityMatrices::BestMove NwGapAffinityMatrices::best_move(int i, int j,
		NwGapAffinityMatrices::BestMove iold_move) {
	switch (iold_move) {
	case NwGapAffinityMatrices::BestMove::NONE:
	case NwGapAffinityMatrices::BestMove::MATCH:
		if ( (matrix_m[i][j] > matrix_ix[i][j]) &&
				(matrix_m[i][j] > matrix_iy[i][j]) ) {
			return NwGapAffinityMatrices::BestMove::MATCH;
		}
		else if (matrix_ix[i][j] > matrix_iy[i][j]) {
			return NwGapAffinityMatrices::BestMove::X;
		}
		else {
			return NwGapAffinityMatrices::BestMove::Y;
		}
	case NwGapAffinityMatrices::BestMove::X:
		if ( ((matrix_m[i][j] - gap_open) > matrix_ix[i][j]) &&
				((matrix_m[i][j] - gap_open) > (matrix_iy[i][j] - gap_open)) ) {
			return NwGapAffinityMatrices::BestMove::MATCH;
		}
		else if (matrix_ix[i][j] > (matrix_iy[i][j] - gap_open)) {
			return NwGapAffinityMatrices::BestMove::X;
		}
		else {
			return NwGapAffinityMatrices::BestMove::Y;
		}
		break;
	case NwGapAffinityMatrices::BestMove::Y:
		if ( ((matrix_m[i][j] - gap_open) > (matrix_ix[i][j] - gap_open)) &&
				((matrix_m[i][j] - gap_open) > matrix_iy[i][j]) ) {
			return NwGapAffinityMatrices::BestMove::MATCH;
		}
		else if ((matrix_ix[i][j] - gap_open) > matrix_iy[i][j]) {
			return NwGapAffinityMatrices::BestMove::X;
		}
		else {
			return NwGapAffinityMatrices::BestMove::Y;
		}
		break;
	}

	assert(false); // Should newer occur.
	return NwGapAffinityMatrices::BestMove::NONE;
}


float NwGapAffinityMatrices::global_alignment_best_score() {
	int i_max = matrix_m.size() - 1;
	int j_max = matrix_m[0].size() - 1;
	return std::max( { matrix_m[i_max][j_max], matrix_ix[i_max][j_max], matrix_iy[i_max][j_max] } );
}


void NwGapAffinityMatrices::print_matrix(std::vector<std::vector<float> > *matrix) {
	for (size_t i=0; i<matrix->size(); i++) {
		for (size_t j=0; j<(*matrix)[i].size(); j++) {
			printf("%12.1f", (float)(*matrix)[i][j]);
		}
		std::cout << std::endl;
	}
}


