/*
 * testcomplexitysimilartiy.hpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONSIMILARITY_HPP_
#define NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONSIMILARITY_HPP_


namespace nscsearch {
	class TestCompositionSimilarity {
	public:
		void run();

	private:
		void initialize_data();

		void calculate_maximal_similarity_score_exact_homopolymers();
		void calculate_maximal_similarity_score_similar_homopolymers();
		void calculate_maximal_similarity_score_different_homopolymers();

		void calculate_maximal_similarity_score_exact_short_tandem_repeats();
		void calculate_maximal_similarity_score_exact_composition_adjacent_homopolymers_vs_short_tandem_repeats();
		void calculate_maximal_similarity_score_similar_short_tandem_repeats();
		void calculate_maximal_similarity_score_different_short_tandem_repeats();

		void calculate_maximal_similarity_score_homopolymer_vs_high_complexity_region();

		void calculate_maximal_similarity_score_replace_hit_residue();
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONSIMILARITY_HPP_ */
