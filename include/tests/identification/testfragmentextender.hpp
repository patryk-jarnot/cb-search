/*
 * testfragmentextender.hpp
 *
 *  Created on: May 19, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTFRAGMENTEXTENDER_HPP_
#define NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTFRAGMENTEXTENDER_HPP_


namespace nscsearch {
	class TestFragmentExtender {
	public:
		void run();

	private:
		void initialize_data();

		void extend_no_operation();
		void extend_fragment_to_left();
		void extend_fragment_to_right();
		void extend_fragment_to_both_sides();
		void extend_fragment_to_the_begin();
		void extend_fragment_to_the_end();
		void extend_fragment_to_both_ends();
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTFRAGMENTEXTENDER_HPP_ */
