/*
 * testfragmentextender.cpp
 *
 *  Created on: May 19, 2023
 *      Author: pjarnot
 */

#include "tests/identification/testfragmentextender.hpp"
#include "identification/fragmentextender.hpp"
#include "tests/unittest.hpp"


#include <iostream>
#include <vector>
//#include "identification/compositionidentificator.hpp"
#include "identification/frequencyidentificator.hpp"

using namespace std;

namespace nscsearch {
	void TestFragmentExtender::run() {
		initialize_data();

		extend_no_operation();
		extend_fragment_to_left();
		extend_fragment_to_right();
		extend_fragment_to_both_sides();
		extend_fragment_to_the_begin();
		extend_fragment_to_the_end();
		extend_fragment_to_both_ends();

		std::cerr << "\n";
	}

	void TestFragmentExtender::initialize_data() {

	}

	void TestFragmentExtender::extend_no_operation() {
		std::vector<identification_result_t> best_score_fragments {identification_result_t{4, 8}};
		vector<float> smoothed_scores {0,0,0,5,0,0,0};

		FragmentExtender fe;
		fe.extend_fragment(&best_score_fragments[0].begin, &best_score_fragments[0].end, smoothed_scores);

		ASSERT(best_score_fragments[0].begin == 4);
		ASSERT(best_score_fragments[0].end == 8);
	}

	void TestFragmentExtender::extend_fragment_to_left() {
		std::vector<identification_result_t> best_score_fragments {identification_result_t{4, 8}};
		vector<float> smoothed_scores {0,0,5,5,0,0,0};

		FragmentExtender fe;
		fe.extend_fragment(&best_score_fragments[0].begin, &best_score_fragments[0].end, smoothed_scores);

		ASSERT(best_score_fragments[0].begin == 3);
		ASSERT(best_score_fragments[0].end == 8);
	}

	void TestFragmentExtender::extend_fragment_to_right() {
		std::vector<identification_result_t> best_score_fragments {identification_result_t{4, 8}};
		vector<float> smoothed_scores {0,0,0,5,5,0,0};

		FragmentExtender fe;
		fe.extend_fragment(&best_score_fragments[0].begin, &best_score_fragments[0].end, smoothed_scores);

		ASSERT(best_score_fragments[0].begin == 4);
		ASSERT(best_score_fragments[0].end == 9);
	}

	void TestFragmentExtender::extend_fragment_to_both_sides() {
		std::vector<identification_result_t> best_score_fragments {identification_result_t{4, 8}};
		vector<float> smoothed_scores {0,0,5,5,5,0,0};

		FragmentExtender fe;
		fe.extend_fragment(&best_score_fragments[0].begin, &best_score_fragments[0].end, smoothed_scores);

		ASSERT(best_score_fragments[0].begin == 3);
		ASSERT(best_score_fragments[0].end == 9);
	}

	void TestFragmentExtender::extend_fragment_to_the_begin() {
		std::vector<identification_result_t> best_score_fragments {identification_result_t{4, 8}};
		vector<float> smoothed_scores {5,5,5,5,0,0,0};

		FragmentExtender fe;
		fe.extend_fragment(&best_score_fragments[0].begin, &best_score_fragments[0].end, smoothed_scores);

		ASSERT(best_score_fragments[0].begin == 1);
		ASSERT(best_score_fragments[0].end == 8);
	}

	void TestFragmentExtender::extend_fragment_to_the_end() {
		std::vector<identification_result_t> best_score_fragments {identification_result_t{4, 8}};
		vector<float> smoothed_scores {0,0,0,5,5,5,5};

		FragmentExtender fe;
		fe.extend_fragment(&best_score_fragments[0].begin, &best_score_fragments[0].end, smoothed_scores);

		ASSERT(best_score_fragments[0].begin == 4);
		ASSERT(best_score_fragments[0].end == 11);
	}

	void TestFragmentExtender::extend_fragment_to_both_ends() {
		std::vector<identification_result_t> best_score_fragments {identification_result_t{4, 8}};
		vector<float> smoothed_scores {5,5,5,5,5,5,5};

		FragmentExtender fe;
		fe.extend_fragment(&best_score_fragments[0].begin, &best_score_fragments[0].end, smoothed_scores);

		ASSERT(best_score_fragments[0].begin == 1);
		ASSERT(best_score_fragments[0].end == 11);
	}
}


