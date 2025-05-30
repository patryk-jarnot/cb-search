/*
 * testscoringmatrix.cpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#include "tests/residue/testscoringmatrix.hpp"

#include "model/matrixresidue.hpp"

#include "tests/unittest.hpp"

#include <iostream>
#include "residue/scoringmatrix.hpp"

using namespace nscsearch;


void TestScoringMatrix::run() {
	blosum62_check_matches();
	blosum62_check_mismatches();
	blosum62_check_mask_residues_diagonal();

	residue_to_char_conversion_three_examples();
	std::cout << "\n";
}


void TestScoringMatrix::blosum62_check_matches() {
	ScoringMatrix sm;
	sm.select(ScoringMatrix::Types::BLOSUM62);

	ASSERT(sm.get_score('C', 'C') == 9);
	ASSERT(sm.get_score('P', 'P') == 7);
	ASSERT(sm.get_score('Q', 'Q') == 5);
	ASSERT(sm.get_score('H', 'H') == 8);
	ASSERT(sm.get_score('M', 'M') == 5);
	ASSERT(sm.get_score('W', 'W') == 11);
	ASSERT(sm.get_score('I', 'I') == 4);
	ASSERT(sm.get_score('D', 'D') == 6);
}


void TestScoringMatrix::blosum62_check_mismatches() {
	ScoringMatrix sm;
	sm.select(ScoringMatrix::Types::BLOSUM62);

	ASSERT(sm.get_score('C', 'P') == -3);
	ASSERT(sm.get_score('S', 'N') == 1);
	ASSERT(sm.get_score('Q', 'M') == 0);
	ASSERT(sm.get_score('I', 'V') == 3);
	ASSERT(sm.get_score('D', 'L') == -4);
}


void TestScoringMatrix::blosum62_check_mask_residues_diagonal() {
	ScoringMatrix sm;
	sm.select(ScoringMatrix::Types::BLOSUM62);
	sm.mask_residues_except_diagonal({'R', 'P'}, 0);

	ASSERT(sm.get_score('C', 'P') == 0);
	ASSERT(sm.get_score('S', 'N') == 0);
	ASSERT(sm.get_score('Q', 'M') == 0);
	ASSERT(sm.get_score('I', 'V') == 0);
	ASSERT(sm.get_score('D', 'L') == 0);
	ASSERT(sm.get_score('R', 'R') == 5);
	ASSERT(sm.get_score('P', 'P') == 7);
	ASSERT(sm.get_score('A', 'A') == 0);
}


void TestScoringMatrix::residue_to_char_conversion_three_examples() {
	ASSERT(residue_to_char(MatrixResidue::A) == 'A');
	ASSERT(residue_to_char(MatrixResidue::X) == 'X');
	ASSERT(residue_to_char(MatrixResidue::Q) == 'Q');
}





