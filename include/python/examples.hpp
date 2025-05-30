/*
 * examples.hpp
 *
 *  Created on: Jun 13, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_PYTHON_EXAMPLES_HPP_
#define NSCSEARCH_INCLUDE_PYTHON_EXAMPLES_HPP_


#include <string>
#include <vector>


struct example_result_t {
	int begin;
	int end;
};

std::vector<example_result_t> take_strings_return_vector_of_struct(std::string iquery, std::string isequence);
std::vector<int> take_strings_return_vector_of_ints(std::string iquery, std::string isequence);
void take_strings(std::string iquery, std::string isequence);
void take_struct(example_result_t iexample_result);


#endif /* NSCSEARCH_INCLUDE_PYTHON_EXAMPLES_HPP_ */
