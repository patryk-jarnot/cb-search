/*
 * testgapaffinitymatrices.cpp
 *
 *  Created on: Mar 27, 2023
 *      Author: pjarnot
 */

#include "tests/alignment/nw/testnwgapaffinitymatrices.hpp"
#include "alignment/nw/nwgapaffinitymatrices.hpp"

#include "debug.hpp"

#include "tests/unittest.hpp"

#include <iostream>

using namespace nscsearch;
using namespace std;


void TestNwGapAffinityMatrices::run() {
	initialize_data();

	test_identical_sequences();
	test_different_sequences();
	test_similar_residues();
	test_hit_shift_in_alignment();
	test_sequences_of_different_length();
	test_mask_residue_negative_mask();

	std::cerr << "\n";
}


void TestNwGapAffinityMatrices::initialize_data() {
	gap_open = 3;
	gap_extend = 1;

	sequences.resize(10);


	sequences[0] = "AAAA";  // index: 0
	sequences[1] = "DDDD";
	sequences[2] = "LLLL";
	sequences[3] = "AAAAAADDDDDDAAAAAA";
	sequences[4] = "AAAAAAAAAAAA";
	sequences[5] = "EEDD";  // index: 5
	sequences[6] = "EDED";
	sequences[7] = "AAEDED";
	sequences[8] = "GGLG";
	sequences[9] = "GGG";  // index: 9

}


void TestNwGapAffinityMatrices::test_identical_sequences() {
	NwGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices(sequences[0], sequences[0], gap_open, gap_extend);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(2, 2) == 8);
	ASSERT(gam.get_m_value(4, 4) == 16);

	ASSERT(gam.get_ix_value(0, 1) == -4);
	ASSERT(gam.get_ix_value(0, 2) == -5);
	ASSERT(gam.get_ix_value(4, 4) == 4);

	ASSERT(gam.get_iy_value(4, 4) == 4);
}


void TestNwGapAffinityMatrices::test_different_sequences() {
	NwGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices(sequences[1], sequences[2], 2, 1);

	ASSERT(gam.get_m_value(4, 4) == -14);
	ASSERT(gam.get_ix_value(4, 4) == -12);
	ASSERT(gam.get_iy_value(4, 4) == -12);
}


void TestNwGapAffinityMatrices::test_similar_residues() {
	NwGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices(sequences[5], sequences[6], 2, 1);

	ASSERT(gam.get_m_value(4, 4) == 15);
	ASSERT(gam.get_ix_value(4, 4) == 10);
	ASSERT(gam.get_iy_value(4, 4) == 7);
}


void TestNwGapAffinityMatrices::test_hit_shift_in_alignment() {
	NwGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices(sequences[8], sequences[9], 2, 1);

//	gam.print_matrix_m();
//	gam.print_matrix_ix();
//	gam.print_matrix_iy();

	ASSERT(gam.get_m_value(3, 4) == 15);
	ASSERT(gam.get_ix_value(3, 4) == 5);
	ASSERT(gam.get_iy_value(3, 4) == 5);

	ASSERT(gam.best_move(1, 1, NwGapAffinityMatrices::BestMove::MATCH) == NwGapAffinityMatrices::BestMove::MATCH);
	ASSERT(gam.best_move(2, 2, NwGapAffinityMatrices::BestMove::X) == NwGapAffinityMatrices::BestMove::MATCH);
	ASSERT(gam.best_move(2, 3, NwGapAffinityMatrices::BestMove::MATCH) == NwGapAffinityMatrices::BestMove::X);
	ASSERT(gam.best_move(3, 4, NwGapAffinityMatrices::BestMove::NONE) == NwGapAffinityMatrices::BestMove::MATCH);
}


void TestNwGapAffinityMatrices::test_sequences_of_different_length() {
	NwGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGM", "MGGMGGMGGMGGM", 2, 1);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(1, 1) == 5);
}


void TestNwGapAffinityMatrices::test_mask_residue_negative_mask() {
	NwGapAffinityMatrices gam;
	ScoringMatrix sm;

	sm.mask_residues_except_diagonal({'G'}, -1);

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGMGGM", "MGGMGGMGGMGGM", 2, 1);

//	std::cerr << "gam.get_m_value(1, 1): " << gam.get_m_value(1, 1) << "\n";

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(1, 1) == -1);
}

