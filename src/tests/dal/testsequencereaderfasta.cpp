/*
 * testsequencereaderfasta.cpp
 *
 *  Created on: May 22, 2023
 *      Author: pjarnot
 */

#include "tests/dal/testsequencereaderfasta.hpp"

#include "tests/unittest.hpp"
#include "debug.hpp"


using namespace std;

namespace nscsearch {

	void TestSequenceReaderFasta::run(std::string iroot_path) {
		root_path = iroot_path;

		init_test_data();

		test_read_sequences_empty_file();
		test_read_single_sequence();
		test_read_multiple_sequences();

		std::cerr << "\n";
	}

	void TestSequenceReaderFasta::init_test_data() {
	}

	void TestSequenceReaderFasta::test_read_sequences_empty_file() {
		SequenceReaderFasta srf;
		srf.open_file(root_path + "/src/tests/data/empty.txt");
		ASSERT(false == srf.has_next_sequence());
	}

	void TestSequenceReaderFasta::test_read_single_sequence() {
		SequenceReaderFasta srf;
		srf.open_file(root_path + "/src/tests/data/query_1_lcr.fasta");
		ASSERT(true == srf.has_next_sequence());
		Sequence sequence = srf.get_next_sequence();
		ASSERT(sequence.get_header().compare(">querysequence1") == 0);
		ASSERT(sequence.get_sequence().compare("AAAAAA") == 0);
		ASSERT(false == srf.has_next_sequence());
	}

	void TestSequenceReaderFasta::test_read_multiple_sequences() {
		SequenceReaderFasta srf;
		srf.open_file(root_path + "/src/tests/data/db_5_lcrs.fasta");
		ASSERT(true == srf.has_next_sequence());
		Sequence sequence = srf.get_next_sequence();
		ASSERT(sequence.get_header().compare(">sequence1") == 0);
		ASSERT(sequence.get_sequence().compare("AAAAA") == 0);
		ASSERT(true == srf.has_next_sequence());
		sequence = srf.get_next_sequence();
		ASSERT(true == srf.has_next_sequence());
		sequence = srf.get_next_sequence();
		ASSERT(true == srf.has_next_sequence());
		sequence = srf.get_next_sequence();
		ASSERT(true == srf.has_next_sequence());
		sequence = srf.get_next_sequence();
		ASSERT(sequence.get_header().compare(">sequence3") == 0);
		ASSERT(sequence.get_sequence().compare("DDDDDDDD") == 0);
		ASSERT(false == srf.has_next_sequence());
	}

}

