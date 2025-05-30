/*
 * matrixrecalculation.hpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_RESIDUE_MATRIXRECALCULATOR_HPP_
#define NSCSEARCH_INCLUDE_RESIDUE_MATRIXRECALCULATOR_HPP_

#include "constants.hpp"

#include <vector>
#include <string>
#include <map>

namespace nscsearch {
	class MatrixRecalculator {
	public:
		void recalculate(float *imatrix);
		float *get_matrix() { return recalculated_matrix; }
		void mask_residues_except_diagonal(std::vector<char> residues);  // { diagonal_match_residues = residues;}
		void mask_residues_except_diagonal(std::vector<char> residues, float imask_value);
		void cbr_correction(std::string iquery_sequence, float ialpha);

	private:
		float recalculated_matrix[SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE];
		std::vector<char> diagonal_match_residues;
		float mask_value;
		std::map<char, float> residue_frequencies;
		float alpha;

		void recalculate_mask_residues(float *imatrix);
		void recalculate_matrix_cbr_frequencies(float *imatrix);

	};
}


#endif /* NSCSEARCH_INCLUDE_RESIDUE_MATRIXRECALCULATOR_HPP_ */
