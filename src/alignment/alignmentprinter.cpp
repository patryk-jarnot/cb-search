/*
 * alignmentprinter.cpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */

#include "alignment/alignmentprinter.hpp"
#include "utils/stringutils.hpp"

#include "debug.hpp"

#include <iomanip>

using namespace nscsearch;
using namespace std;


AlignmentPrinter::AlignmentPrinter(std::ostream *ostr, int imax_width) {
	output = ostr;
	max_width = imax_width;
}


void AlignmentPrinter::set_query_alignment(std::string iquery_alignment) {
	query_alignment = iquery_alignment;
}


void AlignmentPrinter::set_midline_alignment(std::string imidline_alignment) {
	midline_alignment = imidline_alignment;
}


void AlignmentPrinter::set_hit_alignment(std::string ihit_alignment) {
	hit_alignment = ihit_alignment;
}


void AlignmentPrinter::print_alignment() {
	if (query_alignment.length() != hit_alignment.length()) {
		*output << "Error: query alignment length is not equal to hit alignment length\n";
		return;
	}

	size_t current_alignment_begin = 0;
	while (current_alignment_begin < query_alignment.length()) {
		int remaining_length = (current_alignment_begin + max_width) < query_alignment.length() ? (max_width) : (query_alignment.length() - current_alignment_begin);

		int query_begin_position = replace_all_return(query_alignment.substr(0, current_alignment_begin), "-", "").length()+1;
		int query_end_position = replace_all_return(query_alignment.substr(0, current_alignment_begin+remaining_length), "-", "").length();
		int hit_begin_position = replace_all_return(hit_alignment.substr(0, current_alignment_begin), "-", "").length()+1;
		int hit_end_position = replace_all_return(hit_alignment.substr(0, current_alignment_begin+remaining_length), "-", "").length();

		*output << "Query " << setw(5) << right << query_begin_position << "  " << query_alignment.substr(current_alignment_begin, remaining_length) << "  " << query_end_position << "\n";
		*output << "             " << midline_alignment.substr(current_alignment_begin, remaining_length) << "\n";
		*output << "Hit   " << setw(5) << right << hit_begin_position << "  " << hit_alignment.substr(current_alignment_begin, remaining_length) << "  " << hit_end_position << "\n";

		current_alignment_begin += remaining_length;

		if (current_alignment_begin < query_alignment.length()) {
			*output << "\n";
		}
	}
}


