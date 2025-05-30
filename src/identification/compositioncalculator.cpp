/*
 * complexitycalculator.cpp
 *
 *  Created on: May 4, 2023
 *      Author: pjarnot
 */
#include "identification/compositioncalculator.hpp"

#include "debug.hpp"

#include <string>
#include <cassert>


namespace nscsearch {

	std::map<char, int> CompositionCalculator::count_residues(std::string isequence) {
		std::map<char, int> count_by_residues;

		for (std::string::iterator it=isequence.begin(); it!=isequence.end(); it++) {
			count_by_residues[*it]++;
		}

		return count_by_residues;
	}

	std::vector<int> CompositionCalculator::count_sequence_residues(std::string isequence) {
		std::vector<int> count_by_residues((int)MatrixResidue::STAR);

//		DEBUG("x");
		for (std::string::iterator it=isequence.begin(); it!=isequence.end(); it++) {
			count_by_residues[(int)residue_to_matrix_index(*it)]++;
		}

		return count_by_residues;
	}


	void CompositionCalculator::initialize_count_vector(std::map<char, int> *icount_by_residues) {
		const int RESIDUE_COUNT = 25;
		char residues[RESIDUE_COUNT] = { 'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V', 'B', 'J', 'Z', 'X', '*' };

		for (int i=0; i<RESIDUE_COUNT; i++) {
			(*icount_by_residues)[residues[i]] = 0;
		}
	}

	float CompositionCalculator::identity(std::string ileft_sequence, std::string iright_sequence) {
		assert(ileft_sequence.length() > 0 && iright_sequence.length() == ileft_sequence.length());

		std::vector<int> left_sequence_counts = count_sequence_residues(ileft_sequence);
		std::vector<int> right_sequence_counts = count_sequence_residues(iright_sequence);

		assert(left_sequence_counts.size() == right_sequence_counts.size());

		int same_residue_count = 0;

		for (size_t i=0; i<left_sequence_counts.size(); i++) {
			same_residue_count += std::min(left_sequence_counts[i], right_sequence_counts[i]);
		}

		return (float)same_residue_count / ileft_sequence.length();
	}

}

