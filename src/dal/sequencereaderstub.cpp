/*
 * sequencereaderstub.cpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */




#include "dal/sequencereaderstub.hpp"
#include "model/sequence.hpp"


namespace nscsearch {

	SequenceReaderStub::SequenceReaderStub() : index(0) {

	}

	void SequenceReaderStub::add_sequence(Sequence isequence) {
		sequences.push_back(isequence);
	}

	SequenceReaderStub::~SequenceReaderStub() {

	}

	bool SequenceReaderStub::has_next_sequence() {
		return index < (int)sequences.size();
	}

	Sequence SequenceReaderStub::get_next_sequence() {
		return sequences[index++];
	}

}
