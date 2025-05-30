/*
 * testoggapaffinitymatrices.cpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */


#include "tests/alignment/og/testoggapaffinitymatrices.hpp"
#include "alignment/og/oggapaffinitymatrices.hpp"
#include "utils/numericutils.hpp"

#include "debug.hpp"

#include "tests/unittest.hpp"

#include <iostream>

using namespace nscsearch;
using namespace std;

#define GAP_OPEN 3
#define GAP_EXTEND 1


void test_identical_sequences() {
	OgGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("AAAA", "AAAA", GAP_OPEN, GAP_EXTEND);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(2, 2) == 8);
	ASSERT(gam.get_m_value(4, 4) == 16);

	ASSERT(gam.get_ix_value(0, 1) == -4);
	ASSERT(gam.get_ix_value(0, 2) == -5);
	ASSERT(gam.get_ix_value(4, 4) == 8);

	ASSERT(gam.get_iy_value(4, 4) == 4);
}


void test_sequences_of_different_length() {
	OgGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGM", "MGGMGGMGGMGGM", 2, 1);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(1, 1) == 5);
	ASSERT(gam.get_m_value(10, 10) == 56);
	ASSERT(numbers_equal( gam.get_m_value(13, 10), 56));
}


void test_mask_residue_negative_mask() {
	OgGapAffinityMatrices gam;
	ScoringMatrix sm;

	sm.mask_residues_except_diagonal({'G'}, -1);

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGMGGM", "MGGMGGMGGMGGM", 2, 1);

//	std::cerr << "gam.get_m_value(1, 1): " << gam.get_m_value(1, 1) << "\n";

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(1, 1) == -1);
}


void test_exact_motif_in_long_sequence() {
	OgGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGM", "AAAAAAAAAAAACCCCCCCCCEEEEEEEEMGGMGGMGGMAAAAAAAAAAAACCCCCCCCCEEEEEEEE", 2, 1);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(39, 10) == 56);
}


void test_exact_motif_in_long_sequence_begin() {
	OgGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGM", "MGGMGGMGGMAAAAAAAAAAAACCCCCCCCCEEEEEEEE", 2, 1);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(1, 1) == 5);
	ASSERT(gam.get_m_value(10, 10) == 56);
}


void test_exact_motif_in_long_sequence_end() {
	OgGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGM", "AAAAAAAAAAAACCCCCCCCCEEEEEEEEMGGMGGMGGM", 2, 1);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(39, 10) == 56);
}

void test_shorter_motif_in_long_sequence() {
	OgGapAffinityMatrices gam;
	ScoringMatrix sm;

	gam.set_scoring_matrix(&sm);
	gam.create_matrices("MGGMGGMGGMGGM", "AAAAAAAAAAAACCCCCCCCCEEEEEEEEMGGMGGMGGMAAAAAAAAAAAACCCCCCCCCEEEEEEEE", 2, 1);

	ASSERT(gam.get_m_value(0, 0) == 0);
	ASSERT(gam.get_m_value(39, 13) == 51);
	ASSERT(gam.get_m_value(44, 13) == 51);
}


void TestOgGapAffinityMatrices::run() {
	test_identical_sequences();
	test_sequences_of_different_length();
	test_mask_residue_negative_mask();
	test_exact_motif_in_long_sequence();
	test_exact_motif_in_long_sequence_begin();
	test_exact_motif_in_long_sequence_end();
	test_shorter_motif_in_long_sequence();

	std::cerr << "\n";
}


