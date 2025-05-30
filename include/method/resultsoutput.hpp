/*
 * output.hpp
 *
 *  Created on: Apr 6, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_METHOD_RESULTSOUTPUT_HPP_
#define NSCSEARCH_INCLUDE_METHOD_RESULTSOUTPUT_HPP_

#include "model/results.hpp"

#include <iostream>
#include <string>
#include <vector>
#include "method/options.hpp"


namespace nscsearch {

//struct results_record_t {
//public:
//	std::string query;
//	std::string midline;
//	std::string hit_header;
//	std::string hit_sequence;
//	float score;
//	float identity;
//	float similarity;
//};

class ResultsOutput {
public:
	ResultsOutput();
	ResultsOutput(SortOutputBy isort_by);
	ResultsOutput(SortOutputBy isort_by, float ithreshold);
	void process_record(std::string iquery, std::string imidline, std::string ihit_header, std::string ihit_sequence, float score, float identity, float similarity);
	void print_records(std::ostream *ioutput, results_t *iresults);
	void print_records(std::ostream *ioutput, results_t *iresults, int limit);
	void print_records(std::ostream *ioutput, results_t *iresults, int ilimit, OutputFormat ioutput_format);

	void set_threshold(int ithreshold) { threshold = ithreshold; }

private:
	void sort();
	void filter();
	static bool results_compare(results_item_t left, results_item_t right);

	void print_summary_header();
	void print_summary();
	void print_details();

	void print_json();

//	std::vector<results_record_t> records;
	results_t *results;

	std::ostream *output;
	const size_t HEADER_LENGTH = 55;
	int max_alignment_width;
	float threshold;
	int limit;

	static SortOutputBy sort_by;
};

}


#endif /* NSCSEARCH_INCLUDE_METHOD_RESULTSOUTPUT_HPP_ */
