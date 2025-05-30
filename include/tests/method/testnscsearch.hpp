/*
 * testnsrcsearch.hpp
 *
 *  Created on: Mar 22, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_TESTNSCSEARCH_HPP_
#define NSCSEARCH_INCLUDE_TESTS_TESTNSCSEARCH_HPP_


#include <iostream>

#include "method/options.hpp"

namespace nscsearch {
	class TestNscSearch {
	public:
		void run();

	private:
	void initialize_data();

	void test_serach_sequence();
	void test_serach_sequence_with_composition_identification();
	void test_serach_sequence_out_of_threshold();
	void test_serach_sequence_in_threshold_scope();

	Options opt;
	};
}




#endif /* NSCSEARCH_INCLUDE_TESTS_TESTNSCSEARCH_HPP_ */
