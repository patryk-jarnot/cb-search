/*
 * testfileutils.hpp
 *
 *  Created on: Apr 8, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_UTILS_TESTFILEUTILS_HPP_
#define NSCSEARCH_INCLUDE_TESTS_UTILS_TESTFILEUTILS_HPP_


#include "utils/fileutils.hpp"

#include <iostream>

namespace nscsearch {
	class TestFileUtils {
	public:
		void run(std::string iroot_path);

	private:
		void initialize_data();

		void test_read_whole_file_sequences();
		void test_read_whole_file_missing();
		void test_read_whole_file_empty();

		std::string root_path;
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_UTILS_TESTFILEUTILS_HPP_ */
