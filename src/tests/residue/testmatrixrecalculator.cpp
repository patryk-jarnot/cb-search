/*
 * testmatrixrecalculation.cpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */


#include "tests/residue/testmatrixrecalculator.hpp"

#include "utils/numericutils.hpp"

#include "tests/unittest.hpp"
#include "debug.hpp"

#include <algorithm>
#include <iostream>
#include "residue/matrixrecalculator.hpp"
#include "residue/scoringmatrix.hpp"

using namespace nscsearch;
using namespace std;


void TestMatrixRecalculator::run() {
	mask_residues_no_change();
	mask_residues_all_except_selected_on_diagonal();
    cbr_correction_homopolymer();
    cbr_correction_short_tandem_repeat_perfect();
    cbr_correction_short_tandem_repeat_imperfect();
	std::cout << "\n";
}


void TestMatrixRecalculator::mask_residues_no_change() {
	MatrixRecalculator mr;

	mr.recalculate(blosum62_matrix);

//	for (int i=0; i<25*25; i++) {
//		cerr << mr.get_matrix()[i] << " ; " << blosum62_matrix[i] << "\n";
//	}

	bool (*f)(float, float) = numbers_equal;
	ASSERT(equal(mr.get_matrix(), mr.get_matrix()+SCORING_MATRIX_SIZE*SCORING_MATRIX_SIZE, blosum62_matrix, f));
}



float masked_blosum62_matrix_A_E_diagonal[SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE] = {
/*    A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   J   Z   X   *   */
	  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // A
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // R
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // N
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // D
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // C
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Q
	  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // E
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // G
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // H
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // I
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // L
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // K
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // M
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // F
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // P
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // S
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // T
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // W
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Y
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // V
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // B
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // J
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // Z
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // X
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0  // *
};


void TestMatrixRecalculator::mask_residues_all_except_selected_on_diagonal() {
	MatrixRecalculator mr;

	mr.mask_residues_except_diagonal({'A', 'E'});
	mr.recalculate(blosum62_matrix);

	bool (*f)(float, float) = numbers_equal;
	ASSERT(equal(mr.get_matrix(), mr.get_matrix()+SCORING_MATRIX_SIZE*SCORING_MATRIX_SIZE, masked_blosum62_matrix_A_E_diagonal, f));
}


/*
 * S_ij = alpha * ((F_i + F_j) / 2) * S_ij + (1 - alpha) * S_ij
 */
void TestMatrixRecalculator::cbr_correction_homopolymer() {
	MatrixRecalculator mr;

	mr.cbr_correction("AAAAAAAAA", 0.5);
	mr.recalculate(blosum62_matrix);

    const int MATRIX_A_A_POSITION = 0;  // 4 -> 4
    const int MATRIX_A_Q_POSITION = 5;  // -1 -> -0.75
    const int MATRIX_R_Q_POSITION = SCORING_MATRIX_SIZE + 5;  // 1 -> 0.5

    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_A_A_POSITION], 6.0));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_A_Q_POSITION], -1.0));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_R_Q_POSITION], 0.5));
}


void TestMatrixRecalculator::cbr_correction_short_tandem_repeat_perfect() {
	MatrixRecalculator mr;

	mr.cbr_correction("EDEDEDED", 0.9);
	mr.recalculate(blosum62_matrix);

    const int MATRIX_E_E_POSITION = (int)MatrixResidue::E + SCORING_MATRIX_SIZE * (int)MatrixResidue::E;
    const int MATRIX_D_D_POSITION = (int)MatrixResidue::D + SCORING_MATRIX_SIZE * (int)MatrixResidue::D;
    const int MATRIX_E_D_POSITION = (int)MatrixResidue::E + SCORING_MATRIX_SIZE * (int)MatrixResidue::D;
    const int MATRIX_E_A_POSITION = (int)MatrixResidue::E + SCORING_MATRIX_SIZE * (int)MatrixResidue::A;
    const int MATRIX_K_A_POSITION = (int)MatrixResidue::K + SCORING_MATRIX_SIZE * (int)MatrixResidue::A;
    const int MATRIX_G_A_POSITION = (int)MatrixResidue::G + SCORING_MATRIX_SIZE * (int)MatrixResidue::A;

    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_E_E_POSITION], 9.5));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_D_D_POSITION], 11.4));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_E_D_POSITION], 3.8));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_E_A_POSITION], -1.0));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_K_A_POSITION], -0.1));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_G_A_POSITION], 0.0));
}


void TestMatrixRecalculator::cbr_correction_short_tandem_repeat_imperfect() {
	MatrixRecalculator mr;

	mr.cbr_correction("EDAEDEDED", 0.9);
	mr.recalculate(blosum62_matrix);

    const int MATRIX_E_E_POSITION = (int)MatrixResidue::E + SCORING_MATRIX_SIZE * (int)MatrixResidue::E;
    const int MATRIX_D_D_POSITION = (int)MatrixResidue::D + SCORING_MATRIX_SIZE * (int)MatrixResidue::D;
    const int MATRIX_E_D_POSITION = (int)MatrixResidue::E + SCORING_MATRIX_SIZE * (int)MatrixResidue::D;
    const int MATRIX_E_A_POSITION = (int)MatrixResidue::E + SCORING_MATRIX_SIZE * (int)MatrixResidue::A;
    const int MATRIX_K_A_POSITION = (int)MatrixResidue::K + SCORING_MATRIX_SIZE * (int)MatrixResidue::A;
    const int MATRIX_G_A_POSITION = (int)MatrixResidue::G + SCORING_MATRIX_SIZE * (int)MatrixResidue::A;

    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_E_E_POSITION], 9.5));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_D_D_POSITION], 11.4, 0.001));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_E_D_POSITION], 3.8));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_E_A_POSITION], -1.225));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_K_A_POSITION], -0.325));
    ASSERT(numbers_equal(mr.get_matrix()[MATRIX_G_A_POSITION], 0.0));
}


