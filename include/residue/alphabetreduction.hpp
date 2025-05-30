/*
 * alphabetreduction.hpp
 *
 *  Created on: Jun 6, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_RESIDUE_ALPHABETREDUCTION_HPP_
#define NSCSEARCH_INCLUDE_RESIDUE_ALPHABETREDUCTION_HPP_


#include <string>


namespace nscsearch {

	class AlphabetReduction {
	public:
		char reduce(char iresidue);
		std::string reduce(std::string isequence);

	private:

	};

}


#endif /* NSCSEARCH_INCLUDE_RESIDUE_ALPHABETREDUCTION_HPP_ */
