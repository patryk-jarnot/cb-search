/*
 * identification.hpp
 *
 *  Created on: Jun 13, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_PYTHON_IDENTIFICATION_HPP_
#define NSCSEARCH_INCLUDE_PYTHON_IDENTIFICATION_HPP_


#include <string>
#include <vector>



struct result_t {
	int begin;
	int end;
};

std::vector<float> window_similarity_scores(std::string iquery, std::string isequence);
std::vector<result_t> identify(std::string iquery, std::string isequence, float ifrequency_threshold);


#endif /* NSCSEARCH_INCLUDE_PYTHON_IDENTIFICATION_HPP_ */
