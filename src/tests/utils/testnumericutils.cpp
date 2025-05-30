/*
 * testnumericutils.cpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */

#include "tests/utils/testnumericutils.hpp"

#include "utils/numericutils.hpp"

#include "tests/unittest.hpp"

#include <iostream>


using namespace nscsearch;


void TestNumericUtils::run() {

	initialize_data();
	test_numbers_equal_floats_yes();
	test_numbers_equal_floats_no();

	std::cerr << "\n";
}


void TestNumericUtils::initialize_data() {

}


void TestNumericUtils::test_numbers_equal_floats_yes() {
	float left = 5.110 + 0.001;
	float right = 5.111;

	ASSERT(numbers_equal(left, right) == true);
}


void TestNumericUtils::test_numbers_equal_floats_no() {
	float left = 5.111;
	float right = 5.112;

	ASSERT(numbers_equal(left, right) == false);
}


