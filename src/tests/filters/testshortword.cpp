/*
 * testshortword.cpp
 *
 *  Created on: Jan 12, 2025
 *      Author: pjarnot
 */


#include "tests/filters/testshortword.hpp"
#include "filters/shortword.hpp"

#include "debug.hpp"

#include "tests/unittest.hpp"

#include <iostream>

using namespace nscsearch;
using namespace std;


void test_swf_identical_sequences() {
	string query = "AAAAAAAAAAAAAAAAAAA";
	string db_seqeunce = "QWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNMAAAAAAAAAAAAAAAAAAAQWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNM";

	ShortWordFilter swf;
	swf.set_query(query);
	bool is_similar = swf.is_similar(db_seqeunce);

//	ASSERT(is_similar);
}


void test_swf_similar_sequences() {
	string query = "AAAAAAAAAAAAAAAAAAA";
	string db_seqeunce = "QWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNMAAAAACAAAAAACAAAACAQWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNM";

	ShortWordFilter swf;
	swf.set_query(query);
	bool is_similar = swf.is_similar(db_seqeunce);

//	ASSERT(is_similar);
}


void test_swf_different_repeat_pattern() {
	string query = "AAAAAAAAAAAAAAAAAAAA";
	string db_seqeunce = "QWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNMAQAQAQAQAQAQAQAQAQAQQWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNM";

	ShortWordFilter swf;
	swf.set_query(query);
	bool is_similar = swf.is_similar(db_seqeunce);

	ASSERT(false == is_similar);
}


void test_swf_different_sequences() {
	string query = "AAAAAAAAAAAAAAAAAAA";
	string db_seqeunce = "QWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNMCCCCCCCCCCCCCCCCCCCQWERTYIPASDFGHKLCVNMQWERTYIPASDFGHKLCVNM";

	ShortWordFilter swf;
	swf.set_query(query);
	bool is_similar = swf.is_similar(db_seqeunce);

	ASSERT(false == is_similar);
}


void TestShortWordFilter::run() {
	test_swf_identical_sequences();
	test_swf_similar_sequences();
	test_swf_different_repeat_pattern();
	test_swf_different_sequences();

	std::cerr << "\n";
}




