/*
 * teststringutils.hpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_UTILS_TESTSTRINGUTILS_HPP_
#define NSCSEARCH_INCLUDE_TESTS_UTILS_TESTSTRINGUTILS_HPP_


#include "utils/stringutils.hpp"

#include <iostream>

namespace nscsearch {
	class TestStringUtils {
	public:
		void run();

	private:
		void initialize_data();

		void test_limit_str_shorter();
		void test_limit_str_equal();
		void test_limit_str_longer();

		void test_replace_nothing();
		void test_replace_single_char();
		void test_replace_three_in_row();
		void test_replace_in_two_places();
		void test_replace_and_return();
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_UTILS_TESTSTRINGUTILS_HPP_ */
