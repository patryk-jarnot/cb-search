/*
 * matrixrecalculation.cpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */

#include "residue/matrixrecalculator.hpp"

#include "model/matrixresidue.hpp"
#include "constants.hpp"

#include <iostream>
#include <cstring>
#include "residue/scoringmatrix.hpp"

using namespace nscsearch;


void MatrixRecalculator::recalculate_mask_residues(float *imatrix) {
		int matrix_length = SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE;
		for (int i=0; i<matrix_length; i++) {
			recalculated_matrix[i] = mask_value;
		}
		for (char residue : diagonal_match_residues) {
			int position = (int)residue_to_matrix_index(residue) * SCORING_MATRIX_SIZE + (int)residue_to_matrix_index(residue);
			recalculated_matrix[position] = imatrix[position];
		}
}


float get_frequency_of_residue(std::map<char, float> &iresidue_frequencies, MatrixResidue iresidue) {
	auto frequency_item = iresidue_frequencies.find(residue_to_char(iresidue));
	if (frequency_item != iresidue_frequencies.end()) {
		return frequency_item->second;
	}
	return 0;
}

float cbr_score_function(float ij_score, float i_frequency, float j_frequency, float alpha, float min_frequency, float max_frequency) {
	// S_ij = alpha * ((P_i + P'_j) / 2) * S_ij + (1 - alpha) * S_ij
	return (alpha * 2 * (((i_frequency + j_frequency)/2 - min_frequency) / (max_frequency - min_frequency)) * ij_score)
			+ (1-alpha) * ij_score;
}

void MatrixRecalculator::recalculate_matrix_cbr_frequencies(float *imatrix) {
	float min_frequency = 2;
	float max_frequency = -1;

	for (MatrixResidue i = MatrixResidue::A; i<(MatrixResidue)20; i++) {
		float frequency = get_frequency_of_residue(residue_frequencies, i);
		if (frequency < min_frequency) {
			min_frequency = frequency;
		}
		if (frequency > max_frequency) {
			max_frequency = frequency;
		}
	}

	// Iterate over whole matrix.
	for (MatrixResidue i = MatrixResidue::A; i<MatrixResidue::STAR; i++) {
		float i_frequency_value = get_frequency_of_residue(residue_frequencies, i);

		for (MatrixResidue j = MatrixResidue::A; j<MatrixResidue::STAR; j++) {
			float j_frequency_value = get_frequency_of_residue(residue_frequencies, j);

			int index = (int)i + SCORING_MATRIX_SIZE * (int)j;

			recalculated_matrix[index] = cbr_score_function(imatrix[index], i_frequency_value, j_frequency_value, alpha, min_frequency, max_frequency);
		}
	}
}


void MatrixRecalculator::recalculate(float *imatrix) {
	if (diagonal_match_residues.size() != 0) {
		recalculate_mask_residues(imatrix);
	}
	else if (residue_frequencies.size() != 0) {
		recalculate_matrix_cbr_frequencies(imatrix);
	}
	else {
		memcpy(recalculated_matrix, imatrix, SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE * sizeof(float));
	}
}


void MatrixRecalculator::mask_residues_except_diagonal(std::vector<char> residues) {
	mask_residues_except_diagonal(residues, 0);
	residue_frequencies.clear();
}


void MatrixRecalculator::mask_residues_except_diagonal(std::vector<char> residues, float imask_value) {
	diagonal_match_residues.clear();
	diagonal_match_residues.insert(diagonal_match_residues.end(), residues.begin(), residues.end());
	mask_value = imask_value;
}


std::map<char, float> calculate_frequencies(std::string iquery_sequence) {
	std::map<char, int> counts;

	for (auto it=iquery_sequence.begin(); it != iquery_sequence.end(); it++) {
		auto found_element = counts.find(*it);
		if (found_element != counts.end()) {
			found_element->second++;
		}
		else {
			counts[*it] = 1;
		}
	}

	std::map<char, float> frequencies;

	for (auto it=counts.begin(); it != counts.end(); it++) {
		frequencies[it->first] = (float)it->second / iquery_sequence.length();
	}

	return frequencies;
}


void MatrixRecalculator::cbr_correction(std::string iquery_sequence, float ialpha) {
	residue_frequencies = calculate_frequencies(iquery_sequence);
	alpha = ialpha;
	diagonal_match_residues.clear();
}


