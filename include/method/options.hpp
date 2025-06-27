/*
 * options.hpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_OPTIONS_HPP_
#define NSCSEARCH_INCLUDE_OPTIONS_HPP_

#include "model/results.hpp"

#include <string>
#include <limits>


namespace nscsearch {

	enum class AlignAlgorithm {GLOBAL=0, ONE_WAY_GLOBAL, LOCAL};

class Options
{
public:
	Options() :  gap_open(10.0), gap_extension(0.5), threshold(0.7), limit(500),
		thread_count(1), debug_level(0), alpha_of_cbr_correction(-1), similarity_threshold(0.7), relative_threshold(0.1),
		is_composition_identification(false), kmer_filter_threshold(0.3), sort_output_by(SortOutputBy::SIMI_SCORE), output_format(OutputFormat::HUMAN),
		align_algorithm(AlignAlgorithm::ONE_WAY_GLOBAL) {
	}
	virtual ~Options() {}

	int parse_options(int argc, char **argv);
	int parse_general_options(int argc, char **argv);
	void show_help();

	std::string get_query_file_path() { return query_file_path; }
	std::string get_database_file_path() { return database_file_path; }
	std::string get_output_file_path() { return output_file_path; }
	float get_gap_open() { return gap_open; }
	float get_gap_extension() { return gap_extension; }
	float get_threshold() { return threshold; }
	int get_limit() { return limit; }
	int get_thread_count() { return thread_count; }
	int get_debug_level() { return debug_level; }
	std::string get_unmasked_residues() { return unmasked_residues; }
	SortOutputBy get_sort_output_by() { return sort_output_by; }
	AlignAlgorithm get_align_algorithm() { return align_algorithm; }
	float get_alpha_of_cbr_correction() { return alpha_of_cbr_correction; }
	float get_similarity_threshold() { return similarity_threshold; }
	float get_relative_threshold() { return relative_threshold; }
	bool get_is_composition_identification() { return is_composition_identification; }
	float get_kmer_filter_threshold() { return kmer_filter_threshold; }
	OutputFormat get_output_format() { return output_format; }

	void set_is_composition_identification(bool iis_composition_identification) { is_composition_identification = iis_composition_identification; }
	void set_threshold(float ithreshold) { threshold = ithreshold; }
	void set_align_algorithm(AlignAlgorithm iaa) { align_algorithm = iaa; }

private:
	std::string query_file_path;
	std::string database_file_path;
	std::string output_file_path;
	float gap_open;
	float gap_extension;
	float threshold;
	int limit;
	int thread_count;
	int debug_level;
	float alpha_of_cbr_correction;
	float similarity_threshold;
	float relative_threshold;
	bool is_composition_identification;
	float kmer_filter_threshold;
	std::string unmasked_residues;
	SortOutputBy sort_output_by;
	OutputFormat output_format;
	AlignAlgorithm align_algorithm;
};
}


#endif /* NSCSEARCH_INCLUDE_OPTIONS_HPP_ */

