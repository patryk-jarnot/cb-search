/*
 * testnumericutils.hpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_UTILS_TESTNUMERICUTILS_HPP_
#define NSCSEARCH_INCLUDE_TESTS_UTILS_TESTNUMERICUTILS_HPP_



namespace nscsearch {
	class TestNumericUtils {
	public:
		void run();

	private:
		void initialize_data();

		void test_numbers_equal_floats_yes();
		void test_numbers_equal_floats_no();
	};
}



#endif /* NSCSEARCH_INCLUDE_TESTS_UTILS_TESTNUMERICUTILS_HPP_ */
