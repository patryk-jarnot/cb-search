/*
 * alphabetreduction.cpp
 *
 *  Created on: Jun 6, 2023
 *      Author: pjarnot
 */

#include "residue/alphabetreduction.hpp"


namespace nscsearch {

	char AlphabetReduction::reduce(char iresidue) {
		switch (iresidue) {
		case 'C':
			return '1';

		case 'S':
			return '2';
		case 'T':
			return '2';
		case 'A':
			return '2';
		case 'G':
			return '2';
		case 'P':
			return '2';

		case 'D':
			return '3';
		case 'E':
			return '3';
		case 'Q':
			return '3';
		case 'N':
			return '3';

		case 'H':
			return '4';
		case 'R':
			return '4';
		case 'K':
			return '4';

		case 'M':
			return '5';
		case 'I':
			return '5';
		case 'L':
			return '5';
		case 'V':
			return '5';

		case 'W':
			return '6';
		case 'Y':
			return '6';
		case 'F':
			return '6';
		}
		return '0';
	}


	std::string AlphabetReduction::reduce(std::string isequence) {
		for (size_t i=0; i<isequence.length(); i++) {
			isequence[i] = reduce(isequence[i]);
		}
		return isequence;
	}

}



