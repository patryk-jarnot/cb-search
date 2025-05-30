/*
 * testneedlemanwunsch.cpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#include "tests/alignment/nw/testneedlemanwunsch.hpp"
#include "alignment/nw/needlemanwunsch.hpp"

#include "utils/numericutils.hpp"

#include "tests/unittest.hpp"

#include "debug.hpp"

#include <cmath>
#include <iostream>

using namespace nscsearch;
using namespace std;


void TestNeedlemanWunsch::run() {
	init_test_data();

	test_matrix_correctness();
	test_midline();
	test_score();
	test_midline_mask_residues_except_selected_on_diagonal();
	test_alignment_perfect_match();
	std::cerr << "\n";
}

void TestNeedlemanWunsch::init_test_data() {
	sequences = vector<string>(8);
	sequences[0] = "AGEDEDNQNLLLL";
	sequences[1] = "EDEDLLLL";
	sequences[2] = "EDEDSSSLLLL";
	sequences[3] = "AGEDNQN";
	sequences[4] = "AAAAAAAA";
	sequences[5] = "DDDDDDDD";
	sequences[6] = "LLLL";
	sequences[7] = "DDDD";

	gap_open = 10;
	gap_extend = 1;
}


void TestNeedlemanWunsch::test_matrix_correctness() {
}


void TestNeedlemanWunsch::test_midline() {
	NeedlemanWunsch nw_alg;

	nw_alg.align(sequences[0], sequences[1], gap_open, gap_extend);
	ASSERT(nw_alg.get_alignments()[0].midline_alignment == "  EDED   LLLL");

	nw_alg.align(sequences[0], sequences[2], gap_open, gap_extend);
	ASSERT(nw_alg.get_alignments()[0].midline_alignment == "  EDED+ +LLLL");

	nw_alg.align(sequences[0], sequences[3], gap_open, gap_extend);
	ASSERT(nw_alg.get_alignments()[0].midline_alignment == "AGED  NQN    ");

	nw_alg.align(sequences[4], sequences[5], gap_open, gap_extend);
	ASSERT(nw_alg.get_alignments()[0].midline_alignment == "        ");

	nw_alg.align(sequences[6], sequences[7], 2, 1);
	ASSERT(nw_alg.get_alignments()[0].query_alignment == "LLLL----");
	ASSERT(nw_alg.get_alignments()[0].midline_alignment == "        ");
	ASSERT(nw_alg.get_alignments()[0].hit_alignment == "----DDDD");
}


void TestNeedlemanWunsch::test_score() {
	NeedlemanWunsch nw_alg;
	nw_alg.align(sequences[0], sequences[1], gap_open, gap_extend);
	ASSERT(std::fabs(nw_alg.get_alignments()[0].score - (13)) <= std::numeric_limits<float>::epsilon());
	ASSERT(std::fabs(nw_alg.get_alignments()[0].identity - (8.0 / 13)) <= std::numeric_limits<float>::epsilon());  // take care about float error
	ASSERT(std::fabs(nw_alg.get_alignments()[0].similarity - (8.0 / 13)) <= std::numeric_limits<float>::epsilon());

	nw_alg.align(sequences[0], sequences[2], gap_open, gap_extend);
	ASSERT(std::fabs(nw_alg.get_alignments()[0].score - (28)) <= std::numeric_limits<float>::epsilon());
	ASSERT(std::fabs(nw_alg.get_alignments()[0].identity - (8.0 / 13)) <= std::numeric_limits<float>::epsilon());  // take care about float error
	ASSERT(std::fabs(nw_alg.get_alignments()[0].similarity - (10.0 / 13)) <= std::numeric_limits<float>::epsilon());

	nw_alg.align(sequences[0], sequences[3], gap_open, gap_extend);
	ASSERT(std::fabs(nw_alg.get_alignments()[0].score - (12)) <= std::numeric_limits<float>::epsilon());
	ASSERT(std::fabs(nw_alg.get_alignments()[0].identity - (7.0 / 13)) <= std::numeric_limits<float>::epsilon());  // take care about float error
	ASSERT(std::fabs(nw_alg.get_alignments()[0].similarity - (7.0 / 13)) <= std::numeric_limits<float>::epsilon());

	nw_alg.align(sequences[4], sequences[5], gap_open, gap_extend);
	ASSERT(std::fabs(nw_alg.get_alignments()[0].score - (-16)) <= std::numeric_limits<float>::epsilon());
	ASSERT(std::fabs(nw_alg.get_alignments()[0].identity - (0.0 / 8)) <= std::numeric_limits<float>::epsilon());  // take care about float error
	ASSERT(std::fabs(nw_alg.get_alignments()[0].similarity - (0.0 / 8)) <= std::numeric_limits<float>::epsilon());

	nw_alg.align(sequences[0], sequences[1], gap_open, 0.5);
	ASSERT(std::fabs(nw_alg.get_alignments()[0].score - (15.5)) <= std::numeric_limits<float>::epsilon());
	ASSERT(std::fabs(nw_alg.get_alignments()[0].identity - (8.0 / 13)) <= std::numeric_limits<float>::epsilon());  // take care about float error
	ASSERT(std::fabs(nw_alg.get_alignments()[0].similarity - (8.0 / 13)) <= std::numeric_limits<float>::epsilon());
}


void TestNeedlemanWunsch::test_midline_mask_residues_except_selected_on_diagonal() {
	NeedlemanWunsch nw_alg;

	nw_alg.mask_residues_except_selected_diagonal({'A'});
	nw_alg.align("AAQAAQQQAAAQQQAAAAQQQQAAAA", "AAQQAAQQQQAAAQQAAAAQQQAAAA", 0, 1);
//	cerr << nw_alg.get_query_alignment() << "\n";
//	cerr << nw_alg.get_midline_alignment() << "\n";
//	cerr << nw_alg.get_hit_alignment() << "\n";
	ASSERT(nw_alg.get_alignments()[0].midline_alignment == "AAQ AAQQQ AAAQQ AAAAQQQ AAAA");
}


void TestNeedlemanWunsch::test_alignment_perfect_match() {
	NeedlemanWunsch nw_alg;

	nw_alg.mask_residues_except_selected_diagonal({'G'}, -1);
	nw_alg.align("MGGMGGMGGMGGM", "MGGMGGMGGMGGM", gap_open, gap_extend);

//	nw_alg.print_matrices();

//	cerr << "score: " << nw_alg.get_score() << "\n";
	ASSERT(numbers_equal(43.0, nw_alg.get_alignments()[0].score));
	ASSERT(nw_alg.get_alignments()[0].query_alignment == "MGGMGGMGGMGGM");
	ASSERT(nw_alg.get_alignments()[0].midline_alignment == "MGGMGGMGGMGGM");
	ASSERT(nw_alg.get_alignments()[0].hit_alignment == "MGGMGGMGGMGGM");
}


