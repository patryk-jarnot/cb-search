/*
 * testcomposition.cpp
 *
 *  Created on: Jun 24, 2025
 *      Author: pjarnot
 */


#include "tests/unittest.hpp"

#include "debug.hpp"

#include "filters/composition.hpp"
#include "tests/filters/testcomposition.hpp"


using namespace nscsearch;


void test_filter_sequence() {
	bool filtered = false;

	ASSERT(filtered == true);
}


void TestCompositionFilter::run() {
	test_filter_sequence();

	std::cerr << "\n";
}

