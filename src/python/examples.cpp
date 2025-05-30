/*
 * examples.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: pjarnot
 */

#include "python/examples.hpp"

#include <cassert>


std::vector<example_result_t> take_strings_return_vector_of_struct(std::string iquery, std::string isequence) {
	assert(iquery.compare("str1") == 0);
	assert(isequence.compare("str2") == 0);

	std::vector<example_result_t> retval;

	retval.push_back(example_result_t{5, 4});
	return retval;
}


std::vector<int> take_strings_return_vector_of_ints(std::string iquery, std::string isequence) {
	assert(iquery.compare("str1") == 0);
	assert(isequence.compare("str2") == 0);

	std::vector<int> retval;

	retval.push_back(8);
	retval.push_back(1);
	return retval;
}


void take_strings(std::string iquery, std::string isequence) {
	assert(iquery.compare("str1") == 0);
	assert(isequence.compare("str2") == 0);
}


void take_struct(example_result_t iexample_result) {
	assert(iexample_result.begin == 5);
	assert(iexample_result.end == 10);
}



