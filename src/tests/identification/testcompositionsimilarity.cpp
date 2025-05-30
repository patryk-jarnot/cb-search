/*
 * testcomplexitysimilarity.cpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */

#include "utils/numericutils.hpp"

#include "tests/unittest.hpp"
#include "debug.hpp"

#include <iostream>
#include <string>
#include "identification/compositionsimilarity.hpp"
#include "tests/identification/testcompositionsimilarity.hpp"


namespace nscsearch {
	void TestCompositionSimilarity::run() {
		initialize_data();

		calculate_maximal_similarity_score_exact_homopolymers();
		calculate_maximal_similarity_score_similar_homopolymers();
		calculate_maximal_similarity_score_different_homopolymers();
//		calculate_maximal_similarity_score_different_lengths_homopolymers();

		calculate_maximal_similarity_score_exact_short_tandem_repeats();
		calculate_maximal_similarity_score_exact_composition_adjacent_homopolymers_vs_short_tandem_repeats();
		calculate_maximal_similarity_score_similar_short_tandem_repeats();
		calculate_maximal_similarity_score_different_short_tandem_repeats();

		calculate_maximal_similarity_score_homopolymer_vs_high_complexity_region();

		calculate_maximal_similarity_score_replace_hit_residue();

		std::cerr << "\n";
	}

	void TestCompositionSimilarity::initialize_data() {

	}


	void TestCompositionSimilarity::calculate_maximal_similarity_score_exact_homopolymers() {
		std::string sequence = "HHHHHHHH";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence, sequence, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, 64));
	}

	void TestCompositionSimilarity::calculate_maximal_similarity_score_similar_homopolymers() {
		std::string sequence_query = "DDDDDDDDDD";
		std::string sequence_hit = "EEEEEEEEEE";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, 20));
	}

	/**
	 * IIIIIIIIII----------
	 * ----------GGGGGGGGGG
	 */
	void TestCompositionSimilarity::calculate_maximal_similarity_score_different_homopolymers() {
		std::string sequence_query = "IIIIIIIIII";
		std::string sequence_hit = "GGGGGGGGGG";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, -40));
	}

	void TestCompositionSimilarity::calculate_maximal_similarity_score_exact_short_tandem_repeats() {
		std::string sequence_query = "SRSRSRSRSRSRSR";
		std::string sequence_hit = sequence_query;

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, 63));
	}

	void TestCompositionSimilarity::calculate_maximal_similarity_score_exact_composition_adjacent_homopolymers_vs_short_tandem_repeats() {
		std::string sequence_query = "SRSRSRSRSRSRSR";
		std::string sequence_hit =   "RRRRRRRSSSSSSS";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, 63));
	}

	void TestCompositionSimilarity::calculate_maximal_similarity_score_similar_short_tandem_repeats() {
		std::string sequence_query = "SRSRSRSRSRSRSR";
		std::string sequence_hit =   "SRSKSRSRSKSRSK";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, 54));
	}

	void TestCompositionSimilarity::calculate_maximal_similarity_score_different_short_tandem_repeats() {
		std::string sequence_query = "SRSRSRSRSRSRSR";
		std::string sequence_hit =   "RAQRAQRAQRAQRA";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, 32));
	}

	void TestCompositionSimilarity::calculate_maximal_similarity_score_homopolymer_vs_high_complexity_region() {
		std::string sequence_query = "PPPPPPPPP";
		std::string sequence_hit =   "QWERTNMPV";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();

		ASSERT(numbers_equal(similarity, -8));
	}

	void TestCompositionSimilarity::calculate_maximal_similarity_score_replace_hit_residue() {
		std::string sequence_query = "PPPPPPPPP";
		std::string sequence_hit =   "QWERTNMPV";

		CompositionSimilarity cs;
		ScoringMatrix sm;

		cs.precalculations();
		cs.initialize_calculator(sequence_query, sequence_hit, &sm);
		float similarity = cs.calculate_maximal_similarity();
		ASSERT(numbers_equal(similarity, -8));

		cs.replace_hit_residue('Q', 'P');
		similarity = cs.calculate_maximal_similarity();
		ASSERT(numbers_equal(similarity, 0));
	}
}


