/*
 * testalphabetreduction.cpp
 *
 *  Created on: Jun 6, 2023
 *      Author: pjarnot
 */

#include "tests/residue/testalphabetreduction.hpp"
#include "residue/alphabetreduction.hpp"

#include "tests/unittest.hpp"


namespace nscsearch {

	void test_reduce_residues() {
		AlphabetReduction ar;

		ASSERT(ar.reduce('C') == '1');

		ASSERT(ar.reduce('S') == '2');
		ASSERT(ar.reduce('T') == '2');
		ASSERT(ar.reduce('A') == '2');
		ASSERT(ar.reduce('G') == '2');
		ASSERT(ar.reduce('P') == '2');

		ASSERT(ar.reduce('D') == '3');
		ASSERT(ar.reduce('E') == '3');
		ASSERT(ar.reduce('Q') == '3');
		ASSERT(ar.reduce('N') == '3');

		ASSERT(ar.reduce('H') == '4');
		ASSERT(ar.reduce('R') == '4');
		ASSERT(ar.reduce('K') == '4');

		ASSERT(ar.reduce('M') == '5');
		ASSERT(ar.reduce('I') == '5');
		ASSERT(ar.reduce('L') == '5');
		ASSERT(ar.reduce('V') == '5');

		ASSERT(ar.reduce('W') == '6');
		ASSERT(ar.reduce('Y') == '6');
		ASSERT(ar.reduce('F') == '6');
	}

	void test_reduce_sequence() {
		AlphabetReduction ar;

		ASSERT(ar.reduce(std::string("RAMISRWYFDVTEGKCAPFF")).compare("42552466635232412266") == 0);
	}

	void TestAlphabetReduction::run() {
		test_reduce_residues();
		test_reduce_sequence();

		std::cerr << "\n";
	}

}

