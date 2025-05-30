/*
 * testsmithwaterman.cpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */


#include "tests/unittest.hpp"

#include "debug.hpp"

#include <iostream>
#include "alignment/sw/smithwaterman.hpp"
#include "tests/alignment/sw/testsmithwaterman.hpp"


namespace nscsearch {


	void align_similar_sequences() {
//		SmithWaterman sw_alg;
//
//		sw_alg.align("AAQAAQQQAAAQQQAAAAQQQQAAAA", "AAQQAAQQQQAAAQQAAAAQQQAAAA", 1, 1);
//
//		ASSERT(sw_alg.get_midline_alignment() == "AAQ AAQQQ AAAQQ AAAAQQQ AAAA");
	}

	void align_sequences_shorter_hit() {
//		SmithWaterman sw_alg;
//
//		nw_alg.align("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", 1, 1);
//
//		ASSERT(nw_alg.get_midline_alignment() == "AAAAAAAAAAAAAAAAAAAA");
	}

	void align_sequences_longer_hit() {
//		SmithWaterman sw_alg;
//
//		nw_alg.align("AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 1, 1);
//
//		ASSERT(nw_alg.get_midline_alignment() == "AAAAAAAAAAAAAAAAAAAA");
	}

	void align_sequences_local_similarity() {
//		SmithWaterman sw_alg;
//
//		nw_alg.align("CCCCCCCCCCCCCCAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCC", "DDDDDDDDDDDAAAAAAAAAAAAAAADDDDDDDDDDDDDDDDDDDDD", 1, 1);
//
//		ASSERT(nw_alg.get_midline_alignment() == "AAAAAAAAAAAAAAA");
	}

	void align_sequences_local_similarity_query_begin_hit_end() {
//		SmithWaterman sw_alg;
//
//		nw_alg.align("AAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCC", "DDDDDDDDDDDAAAAAAAAAAAAAAA", 1, 1);
//
//		ASSERT(nw_alg.get_midline_alignment() == "AAAAAAAAAAAAAAA");
	}

	void align_sequences_local_similarity_query_end_hit_begin() {
//		SmithWaterman sw_alg;
//
//		nw_alg.align("CCCCCCCCCCCCCCAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAADDDDDDDDDDDDDDDDDDDDD", 1, 1);
//
//		ASSERT(nw_alg.get_midline_alignment() == "AAAAAAAAAAAAAAA");
	}

	void TestSmithWaterman::run() {
		align_similar_sequences();
		align_sequences_shorter_hit();
		align_sequences_longer_hit();
		align_sequences_local_similarity();
		align_sequences_local_similarity_query_begin_hit_end();
		align_sequences_local_similarity_query_end_hit_begin();

		std::cerr << "\n";
	}
}






