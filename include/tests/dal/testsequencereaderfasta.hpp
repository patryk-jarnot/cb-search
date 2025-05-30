/*
 * testsequencereaderfasta.hpp
 *
 *  Created on: May 22, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_DAL_TESTSEQUENCEREADERFASTA_HPP_
#define NSCSEARCH_INCLUDE_TESTS_DAL_TESTSEQUENCEREADERFASTA_HPP_

#include "dal/sequencereaderfasta.hpp"

namespace nscsearch {
	class TestSequenceReaderFasta {
	public:
		void run(std::string iroot_path);

	private:
		void init_test_data();

		void test_read_sequences_empty_file();
		void test_read_single_sequence();
		void test_read_multiple_sequences();

		std::string root_path;
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_DAL_TESTSEQUENCEREADERFASTA_HPP_ */
