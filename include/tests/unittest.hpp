/*
 * unittest.hpp
 *
 *  Created on: May 16, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_UNITTEST_HPP_
#define NSCSEARCH_INCLUDE_TESTS_UNITTEST_HPP_

#include <cassert>
#include <iostream>

extern int UNIT_TESTS_PASSED_COUNTER;
extern int UNIT_TESTS_FAILED_COUNTER;

#define ASSERT(ASSERT_CONDITION) \
	if (ASSERT_CONDITION) { \
		std::cerr << "\033[32m" << "(OK) " << __FILE__ << ":\033[34m" << __FUNCTION__ << ":" << __LINE__ << "\033[32m:" << #ASSERT_CONDITION << "\033[39;49m" << "\n"; \
		UNIT_TESTS_PASSED_COUNTER++; \
	} \
	else { \
		std::cerr << "\033[31m" << "(FAIL) " << __FILE__ << ":\033[33m" << __FUNCTION__ << ":" << __LINE__ << "\033[31m:" << #ASSERT_CONDITION << "\033[39;49m" << "\n"; \
		UNIT_TESTS_FAILED_COUNTER++; \
	}


#endif /* NSCSEARCH_INCLUDE_TESTS_UNITTEST_HPP_ */
