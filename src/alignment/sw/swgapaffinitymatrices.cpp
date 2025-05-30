/*
 * swgapaffinitymatrices.cpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */



#include "alignment/sw/swgapaffinitymatrices.hpp"

#include "exceptions.hpp"

#include "debug.hpp"
#include "assert.h"

#include <algorithm>
#include <limits>

using namespace nscsearch;
using namespace std;

SwGapAffinityMatrices::SwGapAffinityMatrices() : sm(nullptr), gap_open(0), gap_extend(0) {

}


void SwGapAffinityMatrices::create_matrices(std::string sequence_upper,
		std::string sequence_lower, float gap_open, float gap_extend) {
	assert(sm != nullptr);

	this->sequence_upper = sequence_upper;
	this->sequence_lower = sequence_lower;
	this->gap_open = gap_open;
	this->gap_extend = gap_extend;



	matrix_m = std::vector<std::vector<float> >(sequence_lower.size()+1, std::vector<float>(sequence_upper.size()+1, 0));
	matrix_ix = std::vector<std::vector<float> >(sequence_lower.size()+1, std::vector<float>(sequence_upper.size()+1, 0));
	matrix_iy = std::vector<std::vector<float> >(sequence_lower.size()+1, std::vector<float>(sequence_upper.size()+1, 0));

	fill_matrices();
}


void SwGapAffinityMatrices::fill_ix_first_row() {
//	matrix_ix[0][1] = 0 - gap_open - gap_extend;
//	for (size_t j=2; j<sequence_upper.size()+1; j++) {
//		matrix_ix[0][j] = matrix_ix[0][j-1] - gap_extend;
//	}
}


void SwGapAffinityMatrices::fill_iy_first_column() {
//	matrix_iy[1][0] = 0 - gap_open - gap_extend;
//	for (size_t i=2; i<sequence_lower.size()+1; i++) {
//		matrix_iy[i][0] = matrix_iy[i-1][0] - gap_extend;
//	}
}


void SwGapAffinityMatrices::fill_m_first_column() {
//	for (size_t i=1; i<sequence_lower.size()+1; i++) {
//		matrix_m[i][0] = 0;
//	}
}


void SwGapAffinityMatrices::fill_matrices_body() {
	for (size_t i=1; i<sequence_lower.length()+1; i++) {
		for (size_t j=1; j<sequence_upper.length()+1; j++) {
			int current_match_score = sm->get_score(sequence_lower[i-1], sequence_upper[j-1]);

//			cerr << "i: " << i << "; j: " << j << "; matrix_m[i-1][j-1]: " << matrix_m[i-1][j-1] << "; current_match_score: " << current_match_score << "; sequence_lower[i-1]: " << sequence_lower[i-1] << "; sequence_upper[j-1]: " << sequence_upper[j-1] << "\n";

			matrix_m[i][j] = std::max({ matrix_m[i-1][j-1] + current_match_score,
										matrix_ix[i-1][j-1] + current_match_score,
										matrix_iy[i-1][j-1] + current_match_score,
										0.0f});

			matrix_ix[i][j] = std::max({ matrix_m[i][j-1] - gap_open - gap_extend,
										 matrix_ix[i][j-1] - gap_extend,
										 matrix_iy[i][j-1] - gap_open - gap_extend,
										 0.0f});

			matrix_iy[i][j] = std::max({ matrix_m[i-1][j] - gap_open - gap_extend,
										 matrix_ix[i-1][j] - gap_open - gap_extend,
										 matrix_iy[i-1][j] - gap_extend,
										 0.0f});
		}
	}
}


void SwGapAffinityMatrices::fill_matrices() {
	fill_iy_first_column();
	fill_ix_first_row();
	fill_m_first_column();
	fill_matrices_body();
}


float SwGapAffinityMatrices::get_m_value(int i, int j) {
	return matrix_m[i][j];
}


float SwGapAffinityMatrices::get_ix_value(int i, int j) {
	return matrix_ix[i][j];
}


float SwGapAffinityMatrices::get_iy_value(int i, int j) {
	return matrix_iy[i][j];
}


void SwGapAffinityMatrices::print_matrix_m() {
	std::cout << std::endl << "Matrix M" << std::endl;
	print_matrix(&matrix_m);
}


void SwGapAffinityMatrices::print_matrix_ix() {
	std::cout << std::endl << "Matrix X" << std::endl;
	print_matrix(&matrix_ix);
}


void SwGapAffinityMatrices::print_matrix_iy() {
	std::cout << std::endl << "Matrix Y" << std::endl;
	print_matrix(&matrix_iy);
}

SwGapAffinityMatrices::BestMove SwGapAffinityMatrices::best_move(int i, int j,
		SwGapAffinityMatrices::BestMove iold_move) {
	switch (iold_move) {
	case SwGapAffinityMatrices::BestMove::NONE:
	case SwGapAffinityMatrices::BestMove::MATCH:
		if ( (matrix_m[i][j] > matrix_ix[i][j]) &&
				(matrix_m[i][j] > matrix_iy[i][j]) ) {
			return SwGapAffinityMatrices::BestMove::MATCH;
		}
		else if (matrix_ix[i][j] < matrix_iy[i][j]) {
			return SwGapAffinityMatrices::BestMove::Y;
		}
		else {
			return SwGapAffinityMatrices::BestMove::X;
		}
	case SwGapAffinityMatrices::BestMove::X:
		if ( ((matrix_m[i][j] - gap_open) > matrix_ix[i][j]) &&
				((matrix_m[i][j] - gap_open) > (matrix_iy[i][j] - gap_open)) ) {
			return SwGapAffinityMatrices::BestMove::MATCH;
		}
		else if (matrix_ix[i][j] < (matrix_iy[i][j] - gap_open)) {
			return SwGapAffinityMatrices::BestMove::Y;
		}
		else {
			return SwGapAffinityMatrices::BestMove::X;
		}
		break;
	case SwGapAffinityMatrices::BestMove::Y:
		if ( ((matrix_m[i][j] - gap_open) > (matrix_ix[i][j] - gap_open)) &&
				((matrix_m[i][j] - gap_open) > matrix_iy[i][j]) ) {
			return SwGapAffinityMatrices::BestMove::MATCH;
		}
		else if ((matrix_ix[i][j] - gap_open) < matrix_iy[i][j]) {
			return SwGapAffinityMatrices::BestMove::Y;
		}
		else {
			return SwGapAffinityMatrices::BestMove::X;
		}
		break;
	}

	assert(false); // Should newer occur.
	return SwGapAffinityMatrices::BestMove::NONE;
}

int SwGapAffinityMatrices::get_score(int i, int j) {
	return std::max( { matrix_m[i][j], matrix_ix[i][j], matrix_iy[i][j] } );
}

int SwGapAffinityMatrices::best_score_i_pos() {
	int j_max = matrix_m[0].size() - 1;
	int max_value = std::numeric_limits<int>::min();
	int i_max = -1;
	for (int i=0; i<matrix_m.size(); i++) {
		int cur_max = std::max( { matrix_m[i][j_max], matrix_ix[i][j_max], matrix_iy[i][j_max] } );
		if (cur_max > max_value) {
			max_value = cur_max;
			i_max = i;
		}
	}
	return i_max;
}

void SwGapAffinityMatrices::best_score(int *oi, int *oj) {
	int i_max = -1;
	int j_max = -1;
	int max_value = std::numeric_limits<int>::min();

	for (int i=1; i<matrix_m.size(); i++) {
		for (int j=1; j<matrix_m[i].size(); j++) {
			int cur_max = std::max( { matrix_m[i][j], matrix_ix[i][j], matrix_iy[i][j] } );
			if (cur_max > max_value) {
				max_value = cur_max;
				i_max = i;
				j_max = j;
			}
		}
	}
	*oi = i_max;
	*oj = j_max;
}


float SwGapAffinityMatrices::global_alignment_best_score() {
	int j_max = matrix_m[0].size() - 1;
	int max_value = std::numeric_limits<int>::min();
	for (int i=0; i<matrix_m.size(); i++) {
		int cur_max = std::max( { matrix_m[i][j_max], matrix_ix[i][j_max], matrix_iy[i][j_max] } );
		if (cur_max > max_value) {
			max_value = cur_max;
		}
	}
	return max_value;
}


void SwGapAffinityMatrices::print_matrix(std::vector<std::vector<float> > *matrix) {
	for (size_t i=0; i<matrix->size(); i++) {
		printf("%4i", i);
		for (size_t j=0; j<(*matrix)[i].size(); j++) {
			printf("%11.1f", (float)(*matrix)[i][j]);
		}
		std::cout << std::endl;
	}
}


