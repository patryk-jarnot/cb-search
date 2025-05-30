/*
 * teststringutils.cpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */

#include "tests/utils/teststringutils.hpp"
#include "utils/stringutils.hpp"
#include "utils/numericutils.hpp"

#include "tests/unittest.hpp"
#include "debug.hpp"
#include "assert.h"

#include <string>

using namespace nscsearch;
using namespace std;


void test_jaccard_index_same_sequences() {
	string left = "QWERTYIP";
	string right = "PIYTREWQ";

	float x = jaccard_index(&left, &right);

	ASSERT(x == 1);
}


void test_jaccard_index_different_sequences() {
	string left = "QWERTYIP";
	string right = "ASDFCVNM";

	float x = jaccard_index(&left, &right);

	ASSERT(x == 0);
}


void test_jaccard_index_partialy_similar_sequences() {
	string left = "QWERTYIP";
	string right = "QWERCVNM";

	float x = jaccard_index(&left, &right);

	ASSERT(nscsearch::numbers_equal(x, 4.0/12));
}



void test_jaccard_index_different_lengths() {
	string left = "QWERTYIP";
	string right = "QWER";

	float x = jaccard_index(&left, &right);

	ASSERT(x == 0.5);
}



void test_jaccard_index_different_lengths_different_sequences() {
	string left = "QWERTYIP";
	string right = "ASDF";

	float x = jaccard_index(&left, &right);

	ASSERT(x == 0.0/12);
}


void TestStringUtils::run() {

	initialize_data();

	test_limit_str_shorter();
	test_limit_str_equal();
	test_limit_str_longer();

	test_replace_nothing();
	test_replace_single_char();
	test_replace_three_in_row();
	test_replace_in_two_places();
	test_replace_and_return();

	test_jaccard_index_same_sequences();
	test_jaccard_index_different_sequences();
	test_jaccard_index_partialy_similar_sequences();
	test_jaccard_index_different_lengths();
	test_jaccard_index_different_lengths_different_sequences();

	cerr << "\n";
}


void TestStringUtils::initialize_data() {

}


void TestStringUtils::test_limit_str_shorter() {
	string counter = "1234";

	string limited_counter = limit_str(counter, 5);

//	assert(limited_counter.compare("1234") == 0);
	ASSERT(limited_counter.compare("1234") == 0);
}


void TestStringUtils::test_limit_str_equal() {
	string counter = "12345";

	string limited_counter = limit_str(counter, 5);

	ASSERT(limited_counter.compare("12345") == 0);
}


void TestStringUtils::test_limit_str_longer() {
	string counter = "123456789";

	string limited_counter = limit_str(counter, 5);

	ASSERT(limited_counter.compare("12...") == 0);
}


void TestStringUtils::test_replace_nothing() {
	string counter = "123456789";

	replace_all(counter, "ab", "123");

	ASSERT(counter.compare("123456789") == 0);
}


void TestStringUtils::test_replace_single_char() {
	string counter = "123456789";

	replace_all(counter, "5", "xyz");

	ASSERT(counter.compare("1234xyz6789") == 0);
}


void TestStringUtils::test_replace_three_in_row() {
	string counter = "12345556789";

	replace_all(counter, "5", "x");

	ASSERT(counter.compare("1234xxx6789") == 0);
}


void TestStringUtils::test_replace_in_two_places() {
	string counter = "1234555675589";

	replace_all(counter, "5", "x");

	ASSERT(counter.compare("1234xxx67xx89") == 0);
}


void TestStringUtils::test_replace_and_return() {
	string counter = "1234555675589";

	ASSERT(replace_all_return(counter, "5", "").length() == 8);
}

