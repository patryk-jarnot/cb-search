/*
 * fragment.hpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_MODEL_FRAGMENT_HPP_
#define NSCSEARCH_INCLUDE_MODEL_FRAGMENT_HPP_



#include <string>


namespace nscsearch {
	class Fragment {
	public:
		Fragment(std::string iheader, std::string isequence, int ibegin, int iend);

		std::string get_header() { return header; }
		std::string get_sequence() { return sequence; }
		int get_begin() { return begin; }
		int get_end() { return end; }

	private:
		std::string header;
		std::string sequence;
		int begin;
		int end;
	};
}


#endif /* NSCSEARCH_INCLUDE_MODEL_FRAGMENT_HPP_ */
