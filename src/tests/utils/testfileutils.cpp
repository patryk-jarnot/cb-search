/*
 * testfileutils.cpp
 *
 *  Created on: Apr 8, 2023
 *      Author: pjarnot
 */


#include "tests/utils/testfileutils.hpp"
#include "utils/fileutils.hpp"

#include "exceptions.hpp"

#include "tests/unittest.hpp"

#include <iostream>

using namespace nscsearch;
using namespace std;


void TestFileUtils::run(std::string iroot_path) {

	root_path = iroot_path;

	initialize_data();
	test_read_whole_file_sequences();
	test_read_whole_file_missing();
	test_read_whole_file_empty();

	std::cerr << "\n";
}


void TestFileUtils::initialize_data() {

}


void TestFileUtils::test_read_whole_file_sequences() {
	string expected = ""
			">querysequence1\n"
			"AAAAAA";

	string observed = read_file(root_path + "/src/tests/data/query_1_lcr.fasta");

	ASSERT(observed.compare(expected) == 0);
}


void TestFileUtils::test_read_whole_file_missing() {
	try {
		read_file(root_path + "/path/to/file/which/does/not.exist");
		ASSERT(false);
	}
	catch (FileNotFound &e) {
		// cerr << e.what();
		ASSERT(true);
	}
	catch (exception &) {
		ASSERT(false);
	}
}


void TestFileUtils::test_read_whole_file_empty() {
	string expected = "";

	string observed = read_file(root_path + "/src/tests/data/empty.txt");

	ASSERT(observed.compare(expected) == 0);
}

