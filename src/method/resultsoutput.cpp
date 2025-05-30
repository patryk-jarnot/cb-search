/*
 * output.cpp
 *
 *  Created on: Apr 6, 2023
 *      Author: pjarnot
 */


#include "method/resultsoutput.hpp"

#include "alignment/alignmentprinter.hpp"
#include "utils/stringutils.hpp"
#include "debug.hpp"

#include <algorithm>
#include <iomanip>
#include <limits>


using namespace nscsearch;
using namespace std;


//	results_t *results;
//
//	std::ostream *output;
//	const size_t HEADER_LENGTH = 55;
//	int max_alignment_width;
//	float threshold;
//	int limit;


SortOutputBy ResultsOutput::sort_by;

ResultsOutput::ResultsOutput() : ResultsOutput(SortOutputBy::SCORE) {

}


ResultsOutput::ResultsOutput(SortOutputBy isort_by) : results(nullptr), output(nullptr), max_alignment_width(60), threshold(0.1), limit(500) {
	sort_by = isort_by;
}


ResultsOutput::ResultsOutput(SortOutputBy isort_by, float ithreshold) : results(nullptr), output(nullptr), max_alignment_width(60), threshold(ithreshold), limit(500) {
	sort_by = isort_by;
}


void ResultsOutput::print_summary_header() {
	*output << left << setw(HEADER_LENGTH+1) << "Header"<< right << setw(10) << "Score" << right << setw(11) << "SimiScore" << right << setw(10) << "Identity" << right << setw(13) << "Similarity\n";
}


void ResultsOutput::print_summary() {
	print_summary_header();

	int limit_counter = 0;
	for (auto record : results->alignments) {
		if (limit_counter >= limit) {
			break;
		}

		*output << left << setw(HEADER_LENGTH+1) << limit_str(record.hit_header, HEADER_LENGTH)
				<< right << setw(10) << setprecision(10) << defaultfloat << record.score
				<< right << setw(11) << setprecision(4) << fixed << record.simi_score
				<< right << setw(10) << setprecision(4) << fixed << record.identity
				<< right << setw(12) << setprecision(4) << fixed << record.similarity
				<< "\n";

		limit_counter++;
	}
	*output << defaultfloat << "\n\n";
}


void ResultsOutput::print_details() {
	AlignmentPrinter ap(output, max_alignment_width);

	int limit_counter = 0;
	for (auto record : results->alignments) {
		if (limit_counter >= limit) {
			break;
		}

		*output << limit_str(record.hit_header, HEADER_LENGTH + 30) << "\n"
				<< "Score: " << record.score
				<< "    SimiScore: " << record.simi_score
				<< "    Identity: " << record.identity
				<< "    Similarity: " << record.similarity
				<< "\n\n";

		ap.set_query_alignment(record.query_alignment);
		ap.set_midline_alignment(record.midline_alignment);
		ap.set_hit_alignment(record.hit_alignment);
		ap.print_alignment();
		*output << "\n\n";

		limit_counter++;
	}
}


void ResultsOutput::print_json() {
	*output << "{\n";
	*output << "	\"query_header\": \"" << results->query_header << "\",\n";
	*output << "	\"hits\": [\n";

	for (size_t i=0; i<results->alignments.size(); i++) {
		auto record = results->alignments[i];

		if (i >= limit) {
			break;
		}

		*output << "		{\n";
		*output << "			\"query_alignment\": \"" << record.query_alignment << "\",\n";
		*output << "			\"midline\": \"" << record.midline_alignment << "\",\n";
		*output << "			\"hit_alignment\": \"" << record.hit_alignment << "\",\n";
		*output << "			\"hit_header\": \"" << record.hit_header << "\",\n";
		*output << "			\"score\": " << record.score << ",\n";
		*output << "			\"simi_score\": " << record.simi_score << ",\n";
		*output << "			\"similarity\": " << record.similarity << ",\n";
		*output << "			\"identity\": " << record.identity << "\n";
		*output << "		}";

		if ( (i == results->alignments.size()-1) || ((i+1) == limit) ) {
			*output << "\n";
		}
		else {
			*output << ",\n";
		}

	}
	*output << "	]\n";
	*output << "}\n";
}


void ResultsOutput::print_records(std::ostream *ioutput, results_t *iresults) {
	print_records(ioutput, iresults, std::numeric_limits<int>::max());
}


void ResultsOutput::print_records(std::ostream *ioutput, results_t *iresults, int ilimit) {
	print_records(ioutput, iresults, ilimit, OutputFormat::HUMAN);
}


void ResultsOutput::print_records(std::ostream *ioutput, results_t *iresults, int ilimit, OutputFormat ioutput_format) {
	output = ioutput;
	limit = ilimit;
	results = iresults;
	sort();
	filter();

	switch (ioutput_format) {
	case OutputFormat::HUMAN:
		print_summary();
		print_details();
		break;
	case OutputFormat::JSON:
		print_json();
		break;
	}
}


bool ResultsOutput::results_compare(results_item_t left, results_item_t right) {
	switch (sort_by) {
	case SortOutputBy::NONE:
		break;
	case SortOutputBy::SCORE:
		if (left.score > right.score) {
			return true;
		}
		else {
			return false;
		}
		break;
	case SortOutputBy::SIMI_SCORE:
		if (left.simi_score > right.simi_score) {
			return true;
		}
		else {
			return false;
		}
		break;
	case SortOutputBy::IDENTITY:
		if (left.identity > right.identity) {
			return true;
		}
		else {
			return false;
		}
		break;
	case SortOutputBy::SIMILARITY:
		if (left.similarity > right.similarity) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
	return false;
}


void ResultsOutput::sort() {
	std::sort(results->alignments.begin(), results->alignments.end(), results_compare);
}


void ResultsOutput::filter() {
	float val = threshold;
	switch (sort_by) {
	case SortOutputBy::NONE:
		break;
	case SortOutputBy::SCORE:
		results->alignments.erase(remove_if(begin(results->alignments), end(results->alignments), [val](results_item_t const& r)
		{
		    return r.score < val;
		}), end(results->alignments));
		break;
	case SortOutputBy::SIMI_SCORE:
		results->alignments.erase(remove_if(begin(results->alignments), end(results->alignments), [val](results_item_t const& r)
		{
		    return r.simi_score < val;
		}), end(results->alignments));
		break;
	case SortOutputBy::IDENTITY:
		results->alignments.erase(remove_if(begin(results->alignments), end(results->alignments), [val](results_item_t const& r)
		{
		    return r.identity < val;
		}), end(results->alignments));
		break;
	case SortOutputBy::SIMILARITY:
		results->alignments.erase(remove_if(begin(results->alignments), end(results->alignments), [val](results_item_t const& r)
		{
		    return r.similarity < val;
		}), end(results->alignments));
		break;
	}
}


