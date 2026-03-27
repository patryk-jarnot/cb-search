/*
 * options.hpp
 *
 *  Created on: Jan 29, 2026
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_SIMICOMP_OPTIONS_HPP_
#define NSC_SEARCH_INCLUDE_SIMICOMP_OPTIONS_HPP_


#include "model/results.hpp"

#include <string>
#include <limits>

#include <iostream>

namespace nscsearch {

class OptionsSc
{
public:
	OptionsSc() : limit(500), thread_count(1), debug_level(0), similarity_threshold(0.7), relative_threshold(0.1) {
	}
	virtual ~OptionsSc() {}

	int parse_options(int argc, char **argv);
	int parse_general_options(int argc, char **argv);
	void show_help();

	std::string get_query_file_path() { return query_file_path; }
	std::string get_database_file_path() { return database_file_path; }
	std::string get_output_file_path() { return output_file_path; }
	int get_limit() { return limit; }
	int get_thread_count() { return thread_count; }
	int get_debug_level() { return debug_level; }
	float get_similarity_threshold() { return similarity_threshold; }
	float get_relative_threshold() { return relative_threshold; }

private:
	std::string query_file_path;
	std::string database_file_path;
	std::string output_file_path;
	int limit;
	int thread_count;
	int debug_level;
	float similarity_threshold;
	float relative_threshold;
};
}


#endif /* NSC_SEARCH_INCLUDE_SIMICOMP_OPTIONS_HPP_ */
