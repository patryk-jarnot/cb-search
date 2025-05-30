/*
 * testgapaffinitymatrices.hpp
 *
 *  Created on: Mar 27, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_TESTNWGAPAFFINITYMATRICES_HPP_
#define NSCSEARCH_INCLUDE_TESTS_TESTNWGAPAFFINITYMATRICES_HPP_


#include <vector>
#include <string>


namespace nscsearch {
	class TestNwGapAffinityMatrices {
	public:
		void run();

	private:
		void initialize_data();

		void test_identical_sequences();
		void test_different_sequences();
		void test_similar_residues();
		void test_hit_shift_in_alignment();
		void test_sequences_of_different_length();
		void test_mask_residue_negative_mask();

		std::vector<std::string> sequences;
		int gap_open;
		int gap_extend;
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_TESTGAPAFFINITYMATRICES_HPP_ */
