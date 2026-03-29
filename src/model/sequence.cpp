/*
 * sequence.cpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */


#include "model/sequence.hpp"


namespace cbsearch {
	Sequence::Sequence(std::string iheader, std::string isequence) {
		header = iheader;
		sequence = isequence;
	}
}


