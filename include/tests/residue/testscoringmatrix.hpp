/*
 * testscoringmatrix.hpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_TESTSCORINGMATRIX_HPP_
#define NSCSEARCH_INCLUDE_TESTS_TESTSCORINGMATRIX_HPP_

namespace nscsearch {

	class TestScoringMatrix {
	public:
		void run();

	private:
		void blosum62_check_matches();
		void blosum62_check_mismatches();
		void blosum62_check_mask_residues_diagonal();

		void residue_to_char_conversion_three_examples();
	};

}



#endif /* NSCSEARCH_INCLUDE_TESTS_TESTSCORINGMATRIX_HPP_ */
