/*
 * example.cpp
 *
 *  Created on: Jun 12, 2023
 *      Author: pjarnot
 */

#include "python/nscsearch.hpp"

#include "identification/compositioncalculator.hpp"
#include <iostream>
#include "residue/scoringmatrix.hpp"
#include "utils/numericutils.hpp"

#include <stdio.h>
#include <iostream>


using namespace nscsearch;

void example_hello() {
	printf("hello\n");
	std::cout << "hello cpp\n";

	std::string sequence = "AAAAAAAAA";
	CompositionCalculator cc;

	std::map<char, int> occurrence_count_by_residues = cc.count_residues(sequence);

	std::cout << "occurrence_count_by_residues['A']: " << occurrence_count_by_residues['A'] << "\n";
}


void calculata_composition(std::string isequence) {
	CompositionCalculator cc;

	std::map<char, int> occurrence_count_by_residues = cc.count_residues(isequence);

	for (auto occ : occurrence_count_by_residues) {
		std::cout << "occurrence_count_by_residues['" << occ.first << "']: " << occ.second << "\n";
	}
}


