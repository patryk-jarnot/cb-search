/*
 * sequence.hpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_MODEL_SEQUENCE_HPP_
#define NSCSEARCH_INCLUDE_MODEL_SEQUENCE_HPP_

#include <string>


namespace nscsearch {
	class Sequence {
	public:
		Sequence(std::string iheader, std::string isequence);

		std::string get_header() { return header; }
		std::string get_sequence() { return sequence; }

		std::string* get_header_ptr() { return &header; }
		std::string* get_sequence_ptr() { return &sequence; }

	private:
		std::string header;
		std::string sequence;
	};
}



#endif /* NSCSEARCH_INCLUDE_MODEL_SEQUENCE_HPP_ */
