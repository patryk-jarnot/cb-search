/*
 * stringhelper.hpp
 *
 *  Created on: Oct 4, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_STRINGHELPER_HPP_
#define NSCSEARCH_INCLUDE_STRINGHELPER_HPP_

#include <iostream>
#include <vector>


namespace nscsearch {
	std::string reverse_str(std::string &input_str);
	std::string limit_str(std::string &input_str, size_t imax_length);
	std::string replace_all_return(std::string const& istr, std::string const& iold_str, std::string const& inew_str);
	void replace_all(std::string &io_str, std::string const& iold_str, std::string const& inew_str);
	float jaccard_index(std::string *left, std::string *right);

	std::vector<std::string> split(std::string s, const std::string& delimiter);
	std::vector<std::string> split_regex(std::string &s, const std::string& delimiter);
	void ltrim(std::string &s);
	void rtrim(std::string &s);
	void trim(std::string &s);
	std::string ltrim_copy(std::string s);
	std::string rtrim_copy(std::string s);
	std::string trim_copy(std::string s);
}


#endif /* NSCSEARCH_INCLUDE_STRINGHELPER_HPP_ */
