/*
 * options.hpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_METHOD_CBSEARCH_DB_OPTIONS_HPP_
#define NSC_SEARCH_INCLUDE_METHOD_CBSEARCH_DB_OPTIONS_HPP_


#include <string>
#include <limits>

#include <iostream>

namespace cbsearch {

class OptionsCbDb
{
public:
	OptionsCbDb() {
	}
	virtual ~OptionsCbDb() {}

	int parse_options(int argc, char **argv);
	int parse_general_options(int argc, char **argv);
	void show_help();

	std::string get_input_db_path() { return input_db_path; }

private:
	std::string input_db_path;
};
}


#endif /* NSC_SEARCH_INCLUDE_METHOD_CBSEARCH_DB_OPTIONS_HPP_ */
