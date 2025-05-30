/*
 * fragment.cpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */

#include "model/fragment.hpp"

#include <string>

namespace nscsearch {
	Fragment::Fragment(std::string iheader, std::string isequence, int ibegin, int iend) :
		header(iheader), sequence(isequence), begin(ibegin), end(iend) {
	}
}

