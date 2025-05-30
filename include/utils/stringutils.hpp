/*
 * stringhelper.hpp
 *
 *  Created on: Oct 4, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_STRINGHELPER_HPP_
#define NSCSEARCH_INCLUDE_STRINGHELPER_HPP_

#include <iostream>


namespace nscsearch {
	std::string reverse_str(std::string &input_str);
	std::string limit_str(std::string &input_str, size_t imax_length);
	std::string replace_all_return(std::string const& istr, std::string const& iold_str, std::string const& inew_str);
	void replace_all(std::string &io_str, std::string const& iold_str, std::string const& inew_str);
	float jaccard_index(std::string *left, std::string *right);
}


#endif /* NSCSEARCH_INCLUDE_STRINGHELPER_HPP_ */
