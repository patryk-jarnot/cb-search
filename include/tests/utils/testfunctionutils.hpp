/*
 * testfunctionutils.hpp
 *
 *  Created on: May 18, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_UTILS_TESTFUNCTIONUTILS_HPP_
#define NSCSEARCH_INCLUDE_TESTS_UTILS_TESTFUNCTIONUTILS_HPP_



namespace nscsearch {
	class TestFunctionUtils {
	public:
		void run();

	private:
		void initialize_data();

		void smooth_data_flat();
		void smooth_data_single_outlier();
		void smooth_data_real_function();
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_UTILS_TESTFUNCTIONUTILS_HPP_ */
