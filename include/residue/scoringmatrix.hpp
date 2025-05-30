/*
 * scoringmatrix.hpp
 *
 *  Created on: Sep 30, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_SCORINGMATRIX_HPP_
#define NSCSEARCH_INCLUDE_SCORINGMATRIX_HPP_

#include "constants.hpp"

#include "model/matrixresidue.hpp"

#include <vector>
#include <string>
#include "residue/matrixrecalculator.hpp"

namespace nscsearch {

	class ScoringMatrix {
	public:
		enum class Types { BLOSUM62, CUSTOM };
//		enum class Residues { A=0, R, N, D, C, Q, E, G, H, I, L, K, M, F, P, S, T, W, Y, V, B, J, Z, X, STAR};

		ScoringMatrix();
		float get_score(char a, char b);
		float get_score(MatrixResidue a, MatrixResidue b);
		void select(ScoringMatrix::Types itype);
		void mask_residues_except_diagonal(std::vector<char> iresidues, float imask_value);
		void apply_cbr_correction(std::string iquery, float ialpha);

	private:
		void select_blosum62();

		float current_matrix[SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE];
		MatrixRecalculator recalculator;

	};

	extern float blosum62_matrix[SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE];
}


#endif /* NSCSEARCH_INCLUDE_SCORINGMATRIX_HPP_ */
