/*
 * testcomplexitymatrix.hpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONMATRIX_HPP_
#define NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONMATRIX_HPP_


namespace nscsearch {
	class TestCompositionMatrix {
	public:
		void run();

	private:
		void initialize_data();

		void generate_matrix_homopolymer();
		void generate_matrix_short_tandem_repeat();
		void generate_matrix_high_complexity();
		void generate_matrix_different_lengths();
		void replace_hit_residue_same_residue();
		void replace_hit_residue_different_residue();
		void restore_hit_residue_count_();

		void restore_tmp_vectors_after_pop_residue_pair();

	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONMATRIX_HPP_ */
