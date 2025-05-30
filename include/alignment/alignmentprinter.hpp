/*
 * alignmentprinter.hpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_METHOD_ALIGNMENTPRINTER_HPP_
#define NSCSEARCH_INCLUDE_METHOD_ALIGNMENTPRINTER_HPP_

#include <iostream>
#include <string>


namespace nscsearch {
class AlignmentPrinter {
public:
	AlignmentPrinter(std::ostream *ostr, int imax_width);

	void set_query_alignment(std::string iquery_alignment);
	void set_midline_alignment(std::string imidline_alignment);
	void set_hit_alignment(std::string ihit_alignment);

	void print_alignment();
private:
	std::ostream *output;
	int max_width;

	std::string query_alignment;
	std::string midline_alignment;
	std::string hit_alignment;
};
}


#endif /* NSCSEARCH_INCLUDE_METHOD_ALIGNMENTPRINTER_HPP_ */
