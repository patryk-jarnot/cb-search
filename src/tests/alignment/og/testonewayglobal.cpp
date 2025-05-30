/*
 * testonewayglobal.cpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */


#include "tests/unittest.hpp"

#include "debug.hpp"

#include <iostream>
#include "alignment/og/onewayglobal.hpp"
#include "tests/alignment/og/testonewayglobal.hpp"


namespace nscsearch {

	void og_align_similar_sequences() {
		OneWayGlobal og_alg;

		og_alg.align("AAQAAQQQAAAQQQAAAAQQQQAAAA", "AAQQAAQQQQAAAQQAAAAQQQAAAA", 1, 1);

		ASSERT(og_alg.get_alignments()[0].midline_alignment == "AAQ AAQQQ AAAQQ AAAAQQQ AAAA");
	}

	void og_align_sequences_shorter_hit() {
		OneWayGlobal og_alg;

		og_alg.align("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAA", 1, 1);

		ASSERT(og_alg.get_alignments()[0].midline_alignment == "AAAAAAAAAAAAAAAAAAAA          ");
	}

	void og_align_sequences_longer_hit() {
		OneWayGlobal og_alg;

		og_alg.align("AAAAAAAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 1, 1);

		ASSERT(og_alg.get_alignments()[0].midline_alignment == "AAAAAAAAAAAAAAAAAAAA");
	}

	void og_align_sequences_local_similarity() {
		OneWayGlobal og_alg;

		og_alg.align("AAAAAAAAAAAAAAA", "DDDDDDDDDDDAAAAAAAAAAAAAAADDDDDDDDDDDDDDDDDDDDD", 1, 1);

		ASSERT(og_alg.get_alignments()[0].midline_alignment == "AAAAAAAAAAAAAAA");
	}

	void og_align_sequences_local_similarity_query_begin_hit_end() {
		OneWayGlobal og_alg;

		og_alg.align("AAAAAAAAAAAAAAA", "DDDDDDDDDDDAAAAAAAAAAAAAAA", 1, 1);

		ASSERT(og_alg.get_alignments()[0].midline_alignment == "AAAAAAAAAAAAAAA");
	}

	void og_align_sequences_local_similarity_query_end_hit_begin() {
		OneWayGlobal og_alg;

		og_alg.align("AAAAAAAAAAAAAAA", "AAAAAAAAAAAAAAADDDDDDDDDDDDDDDDDDDDD", 1, 1);

		ASSERT(og_alg.get_alignments()[0].midline_alignment == "AAAAAAAAAAAAAAA");
	}

	void TestOneWayGlobal::run() {
		og_align_similar_sequences();
		og_align_sequences_shorter_hit();
		og_align_sequences_longer_hit();
		og_align_sequences_local_similarity();
		og_align_sequences_local_similarity_query_begin_hit_end();
		og_align_sequences_local_similarity_query_end_hit_begin();

		std::cerr << "\n";
	}
}








