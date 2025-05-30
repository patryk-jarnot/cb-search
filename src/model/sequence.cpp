/*
 * sequence.cpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */


#include "model/sequence.hpp"


namespace nscsearch {
	Sequence::Sequence(std::string iheader, std::string isequence) {
		header = iheader;
		sequence = isequence;
	}
}


