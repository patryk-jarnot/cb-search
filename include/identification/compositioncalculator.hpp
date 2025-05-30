/*
 * complexitycalculator.hpp
 *
 *  Created on: May 4, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONCALCULATOR_HPP_
#define NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONCALCULATOR_HPP_


#include <map>
#include "residue/scoringmatrix.hpp"


namespace nscsearch {

	class CompositionCalculator {
	public:
		std::map<char, int> count_residues(std::string isequence);
		std::vector<int> count_sequence_residues(std::string isequence);
		float identity(std::string ileft_sequence, std::string iright_sequence);

		float calculate_maximal_similarity(std::string isequence_query, std::string isequence_hit,
				ScoringMatrix *ism, float igap_open, float igap_extend);
		void initialize_count_vector(std::map<char, int> *icount_by_residues);

	private:

	};

}


#endif /* NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONCALCULATOR_HPP_ */
