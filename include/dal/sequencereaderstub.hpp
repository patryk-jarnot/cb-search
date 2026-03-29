/*
 * sequencereaderstub.hpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */

#ifndef NSRCSEARCH_INCLUDE_DAL_SEQUENCEREADERSTUB_HPP_
#define NSRCSEARCH_INCLUDE_DAL_SEQUENCEREADERSTUB_HPP_


#include "dal/sequencereader.hpp"
#include "model/sequence.hpp"

#include <vector>


namespace nscsearch {

	class SequenceReaderStub : public SequenceReader {
	public:
		SequenceReaderStub();
		virtual ~SequenceReaderStub();
		void add_sequence(cbsearch::Sequence isequence);

		virtual bool has_next_sequence();
		virtual cbsearch::Sequence get_next_sequence();

	private:
		std::vector<cbsearch::Sequence> sequences;
		int index;

	};

}



#endif /* NSRCSEARCH_INCLUDE_DAL_SEQUENCEREADERSTUB_HPP_ */
