/*
 * testsequencefrequency.cpp
 *
 *  Created on: Dec 1, 2023
 *      Author: pjarnot
 */

#include "tests/identification/testsequencefrequency.hpp"
#include "identification/sequencefrequency.hpp"

#include "tests/unittest.hpp"
#include "debug.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

namespace nscsearch {

	void test_calculate_frequency_similarity_exact_homopolymer() {
		string query = "AAAAAAAAAA";
		string hit = "AKIKAYNLTVEGVEGFVRYSRVTKQHVAAAAAAAAAAFLKELRHSKQYENVNLIHYAILTDKRVDIQHL";
		int motif_begin = 27;

		SequenceFrequency sf;
		vector<float> frequencies = sf.calculate_frequency_similarity_for_hit_over_query_window(query, hit);

		auto max_frequency_it = max_element(frequencies.begin(), frequencies.end());
		auto min_frequency_it = min_element(frequencies.begin(), frequencies.end());

		ASSERT(*max_frequency_it == 1.0);
		ASSERT(*min_frequency_it == 0.0);
	}

	void TestSequenceFrequency::run() {
		test_calculate_frequency_similarity_exact_homopolymer();

		std::cerr << "\n";
	}
}
