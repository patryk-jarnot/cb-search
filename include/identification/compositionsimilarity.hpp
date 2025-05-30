/*
 * complexitysimilarity.hpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONSIMILARITY_HPP_
#define NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONSIMILARITY_HPP_

#include <string>

#include "residue/scoringmatrix.hpp"
#include "compositionmatrix.hpp"


namespace nscsearch {

	class CompositionSimilarity {
	public:

		void precalculations();
		void initialize_calculator(std::string isequence_query, std::string isequence_hit,
				ScoringMatrix *ism);
		float calculate_maximal_similarity();
		void replace_hit_residue(char iold_residue, char inew_residue);

	private:

		CompositionMatrix complexity_matrix;

	};

}


#endif /* NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONSIMILARITY_HPP_ */
