/*
 * testneedlemanwunsch.hpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTNEEDLEMANWUNSCH_HPP_
#define NSCSEARCH_INCLUDE_TESTNEEDLEMANWUNSCH_HPP_

#include <iostream>
#include <vector>

namespace nscsearch {
	class TestNeedlemanWunsch {
	public:
		void run();

	private:
		void init_test_data();

		void test_matrix_correctness();
		void test_midline();
		void test_score();
		void test_query_shift_in_alignment();
		void test_hit_shift_in_alignment();
		void test_midline_mask_residues_except_selected_on_diagonal();
		void test_alignment_perfect_match();

		std::vector<std::string> sequences;
		int gap_open;
		int gap_extend;
	};
}

#endif /* NSCSEARCH_INCLUDE_TESTNEEDLEMANWUNSCH_HPP_ */
