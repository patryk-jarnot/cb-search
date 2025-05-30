/*
 * sequencereader.hpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_DAL_SEQUENCEREADER_HPP_
#define NSCSEARCH_INCLUDE_DAL_SEQUENCEREADER_HPP_



#include "model/sequence.hpp"


namespace nscsearch {

	class SequenceReader {
	public:
		virtual ~SequenceReader() {};
		virtual bool has_next_sequence() = 0;
		virtual Sequence get_next_sequence() = 0;
	private:

	};

}




#endif /* NSCSEARCH_INCLUDE_DAL_SEQUENCEREADER_HPP_ */
