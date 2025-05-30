/*
 * testalignmentprinter.hpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_TESTALIGNMENTPRINTER_HPP_
#define NSCSEARCH_INCLUDE_TESTS_TESTALIGNMENTPRINTER_HPP_



namespace nscsearch {
	class TestAlignmentPrinter {
	public:
		void run();

	private:
	void initialize_data();

	void test_single_line_alignment();
	void test_single_full_line_alignment();
	void test_one_residue_over_full_line_alignment();
	void test_two_and_half_line_alignment();

	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_TESTALIGNMENTPRINTER_HPP_ */
