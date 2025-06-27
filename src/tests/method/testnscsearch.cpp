/*
 * testnscsearch.cpp
 *
 *  Created on: Mar 22, 2023
 *      Author: pjarnot
 */


#include "tests/method/testnscsearch.hpp"
#include "alignment/nw/needlemanwunsch.hpp"
#include "model/sequence.hpp"
#include "model/results.hpp"
#include "dal/sequencereaderstub.hpp"

#include "utils/numericutils.hpp"

#include "tests/unittest.hpp"

#include "debug.hpp"

#include <iostream>
#include <sstream>

#include "method/nscsearch.hpp"

using namespace nscsearch;
using namespace std;



void TestNscSearch::initialize_data() {
	opt.set_align_algorithm(AlignAlgorithm::GLOBAL);
}


void TestNscSearch::test_serach_sequence() {
	SequenceReaderStub database_sequences;
	database_sequences.add_sequence(Sequence(">sp|E1C7T6|TYW5_CHICK tRNA wybutosine-synthesizing protein 5 OS=Gallus gallus OX=9031 GN=TYW5 PE=3 SV=1", "MEQREQPAVQVPSLDGVTRERFLRDVYPRREP"));

	SequenceReaderStub query_sequences;
	query_sequences.add_sequence(Sequence(">sp|A2RUC4|TYW5_HUMAN tRNA wybutosine-synthesizing protein 5 OS=Homo sapiens OX=9606 GN=TYW5 PE=1 SV=1", "MAGQHLPVPRLEGVSREQFMQHLYPQRKP"));

	NscSearch ns(&opt, &database_sequences);

	while (query_sequences.has_next_sequence()) {
		Sequence sequence = query_sequences.get_next_sequence();
		results_t result = ns.scan_database(sequence);

		ASSERT(result.alignments.size() == 1);
		if (result.alignments.size() == 1) {
			ASSERT(numbers_equal(result.alignments[0].score, 71.5));
			ASSERT(result.alignments[0].identity == 0.4375);
			ASSERT(result.alignments[0].similarity == 0.71875);
			ASSERT(0 == result.alignments[0].query_alignment.compare("MAGQHLP---VPRLEGVSREQFMQHLYPQRKP"));
			ASSERT(0 == result.alignments[0].midline_alignment.compare("M  +  P   VP L+GV+RE+F++ +YP+R+P"));
			ASSERT(0 == result.alignments[0].hit_alignment.compare("MEQREQPAVQVPSLDGVTRERFLRDVYPRREP"));
		}
	}
}



void TestNscSearch::test_serach_sequence_with_composition_identification() {
	SequenceReaderStub database_sequences;
	database_sequences.add_sequence(Sequence(">header", "QWERPPPPPPPPPPQWER"));

	Options options;
	options.set_is_composition_identification(true);
	options.set_align_algorithm(AlignAlgorithm::GLOBAL);

	NscSearch ns(&options, &database_sequences);
	Sequence sequence(">head_query", "PPPPP");
	results_t result = ns.scan_database(sequence);

	ASSERT(result.alignments.size() == 1);
	ASSERT(result.alignments.size() == 1 && result.alignments[0].hit_alignment.compare("PPPPPPPPPP") == 0);
	ASSERT(result.alignments.size() == 1 && result.alignments[0].fragment_info.begin == 5);
	ASSERT(result.alignments.size() == 1 && result.alignments[0].fragment_info.end == 14);
}


void test_serach_sequence_in_threshold_scope_not_common_kmers() {
	SequenceReaderStub database_sequences;
	database_sequences.add_sequence(Sequence(">sp|E1C7T6|TYW5_CHICK tRNA wybutosine-synthesizing protein 5 OS=Gallus gallus OX=9031 GN=TYW5 PE=3 SV=1", "MEQREQPAVQVPSLDGVTRERFLRDVYPRREP"));

	SequenceReaderStub query_sequences;
	query_sequences.add_sequence(Sequence(">sp|A2RUC4|TYW5_HUMAN tRNA wybutosine-synthesizing protein 5 OS=Homo sapiens OX=9606 GN=TYW5 PE=1 SV=1", "MAGQHLPVPRLEGVSREQFMQHLYPQRKP"));

	Options o;
	o.set_threshold(71);

	NscSearch ns(&o, &database_sequences);

	while (query_sequences.has_next_sequence()) {
		Sequence sequence = query_sequences.get_next_sequence();
		results_t result = ns.scan_database(sequence);

		ASSERT(result.alignments.size() == 0);
	}
}


void TestNscSearch::test_serach_sequence_out_of_threshold() {
	SequenceReaderStub database_sequences;
	database_sequences.add_sequence(Sequence(">sp|E1C7T6|TYW5_CHICK tRNA wybutosine-synthesizing protein 5 OS=Gallus gallus OX=9031 GN=TYW5 PE=3 SV=1", "MEQREQPAVQVPSLDGVTRERFLRDVYPRREP"));

	SequenceReaderStub query_sequences;
	query_sequences.add_sequence(Sequence(">sp|A2RUC4|TYW5_HUMAN tRNA wybutosine-synthesizing protein 5 OS=Homo sapiens OX=9606 GN=TYW5 PE=1 SV=1", "MAGQHLPVPRLEGVSREQFMQHLYPQRKP"));

	Options o;
	o.set_threshold(72);

	NscSearch ns(&o, &database_sequences);

	while (query_sequences.has_next_sequence()) {
		Sequence sequence = query_sequences.get_next_sequence();
		results_t result = ns.scan_database(sequence);

		ASSERT(result.alignments.size() == 0);
	}
}


void TestNscSearch::run() {
	initialize_data();

	test_serach_sequence();
	test_serach_sequence_with_composition_identification();
	test_serach_sequence_in_threshold_scope_not_common_kmers();
	test_serach_sequence_out_of_threshold();

	std::cerr << "\n";
}

