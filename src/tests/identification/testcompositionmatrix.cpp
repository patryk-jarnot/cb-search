/*
 * testcomplexitymatrix.cpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */

#include "utils/numericutils.hpp"

#include "tests/unittest.hpp"
#include "debug.hpp"

#include <map>
#include <iostream>
#include "identification/compositionmatrix.hpp"
#include "tests/identification/testcompositionmatrix.hpp"
#include "residue/scoringmatrix.hpp"

using namespace std;

namespace nscsearch {

	void TestCompositionMatrix::run() {
		initialize_data();
		generate_matrix_homopolymer();
		generate_matrix_short_tandem_repeat();
		generate_matrix_high_complexity();
		generate_matrix_different_lengths();

		replace_hit_residue_same_residue();
		replace_hit_residue_different_residue();

		restore_tmp_vectors_after_pop_residue_pair();

		std::cerr << "\n";
	}

	void TestCompositionMatrix::initialize_data() {

	}

	void TestCompositionMatrix::generate_matrix_homopolymer() {
		CompositionMatrix cm;
		std::string sequence = "HHHHHHHH";

		cm.initialize_matrix(sequence, sequence);

		ASSERT(cm.get_pair_count('H', 'H') == 8);
	}

	void TestCompositionMatrix::generate_matrix_short_tandem_repeat() {
		CompositionMatrix cm;
		std::string sequence = "SRSRSRSRSRSR";

		cm.initialize_matrix(sequence, sequence);

		ASSERT(cm.get_pair_count('S', 'S') == 6);
		ASSERT(cm.get_pair_count('S', 'R') == 6);
		ASSERT(cm.get_pair_count('R', 'S') == 6);
		ASSERT(cm.get_pair_count('R', 'R') == 6);
		ASSERT(cm.get_pair_count('A', 'N') == 0);
	}

	void TestCompositionMatrix::generate_matrix_high_complexity() {
		CompositionMatrix cm;
		std::string sequence_left = "GQTSDRLETV";
		std::string sequence_right = "PKHIKETYGQ";

		cm.initialize_matrix(sequence_left, sequence_right);

//		cm.print_composition_matrix();

//		DEBUG(cm.get_pair_count('V', 'E'));
		ASSERT(cm.get_pair_count('V', 'E') == 1);
		ASSERT(cm.get_pair_count('T', 'T') == 1);
		ASSERT(cm.get_pair_count('T', 'K') == 2);
	}

	void TestCompositionMatrix::generate_matrix_different_lengths() {
		CompositionMatrix cm;
		std::string sequence_left = "GQTSDRLETVVGDRGLWGLV";
		std::string sequence_right = "PKHIKETYGQ";

		cm.initialize_matrix(sequence_left, sequence_right);

//		cm.print_composition_matrix();

		ASSERT(cm.get_pair_count('V', 'K') == 2);

	}

	void TestCompositionMatrix::replace_hit_residue_same_residue() {
		CompositionMatrix cm;
		std::string sequence_left = "QQQQQ";
		std::string sequence_right = "QQQQQ";

		cm.initialize_matrix(sequence_left, sequence_right);

		cm.replace_hit_residue(residue_to_matrix_index('Q'), residue_to_matrix_index('Q'));

		ASSERT(cm.get_hit_residue_count(residue_to_matrix_index('Q')) == 5);
		ASSERT(cm.get_hit_residue_count(residue_to_matrix_index('A')) == 0);
	}

	void TestCompositionMatrix::replace_hit_residue_different_residue() {
		CompositionMatrix cm;
		std::string sequence_left = "QQQQQ";
		std::string sequence_right = "QQQQQ";

		cm.initialize_matrix(sequence_left, sequence_right);

		cm.replace_hit_residue(residue_to_matrix_index('Q'), residue_to_matrix_index('A'));

		ASSERT(cm.get_hit_residue_count(residue_to_matrix_index('Q')) == 4);
		ASSERT(cm.get_hit_residue_count(residue_to_matrix_index('A')) == 1);
	}

	void TestCompositionMatrix::restore_tmp_vectors_after_pop_residue_pair() {
		CompositionMatrix cm;
		std::string sequence_left = "QQQQQ";
		std::string sequence_right = "QQQQQ";

		cm.precalculations();
		cm.initialize_matrix(sequence_left, sequence_right);

		int count = cm.pop_pair_count(residue_to_matrix_index('Q'), residue_to_matrix_index('Q'));
		ASSERT(count == 5);

		cm.restore_tmp_vectors();
		count = cm.pop_pair_count(residue_to_matrix_index('Q'), residue_to_matrix_index('Q'));
		ASSERT(count == 5);

	}
}

