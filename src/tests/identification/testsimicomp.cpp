/*
 * testsimicomp.cpp
 *
 *  Created on: Nov 1, 2024
 *      Author: pjarnot
 */

#include "tests/unittest.hpp"

#include "debug.hpp"

#include <iostream>
#include <vector>
#include <string>
#include "identification/simicomp.hpp"
#include "tests/identification/testsimicomp.hpp"

#define SCORE_THRESHOLD 0.7
#define RELATIVE_THRESHOLD 0.15

namespace nscsearch {

	void identify_homopolymer_of_proline() {
		std::string query = "PPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMPV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 28);
		ASSERT(results.size() > 0 && results[0].end == 36);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);
	}


	void identify_homopolymer_of_proline_begin() {
		std::string query =    "PPPPPPPPP";
		std::string sequence = "PPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMQVQWERTNMPVQWERTNMPVQWERTNMQV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 1);
		ASSERT(results.size() > 0 && results[0].end == 9);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);
	}

	void identify_homopolymer_of_proline_end() {
		std::string query =                                                          "PPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVQWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPP";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);
		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 55);
		ASSERT(results.size() > 0 && results[0].end == 63);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);

//		assert(false);
	}

	void identify_short_tandem_repeat() {
		std::string query = "PRPRPRPRP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVPRPRPRPRPQWERTNMPVQWERTNMPVQWERTNMPV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 28);
		ASSERT(results.size() > 0 && results[0].end == 36);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PRPRPRPRP") == 0);
	}

	void identify_two_homopolymers_of_proline() {
		std::string query = "PPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPPQWERTNMPVQWERTPPPPPPPPPNMPVQWERTNMPV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);


		ASSERT(results.size() == 2);
		ASSERT(results.size() > 0 && results[0].begin == 28);
		ASSERT(results.size() > 0 && results[0].end == 36);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);

		ASSERT(results.size() > 1 && results[1].begin == 51);
		ASSERT(results.size() > 1 && results[1].end == 59);
		ASSERT(results.size() > 1 && sequence.substr(results[1].begin - 1, results[1].end - results[1].begin + 1).compare("PPPPPPPPP") == 0);
	}

	void identify_longer_homopolymer_of_proline() {
		std::string query = "PPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMPV";

		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 28);
		ASSERT(results.size() > 0 && results[0].end == 41);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPPPPPPP") == 0);
//		assert(false);
	}


	void identify_longer_homopolymer_of_proline_with_mutations() {
		std::string query = "PPPPPPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPPPPPAPPPPPAPPPPPPQWERTNMPVQWERTNMPVQWERTNMPV";

		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 28);
		ASSERT(results.size() > 0 && results[0].end == 52);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPPPPPAPPPPPAPPPPPP") == 0);
	}



	void identify_longer_homopolymer_of_proline_with_small_padding_high_window_span() {
		std::string query = "PPPPP";
		std::string sequence = "QWERPPPPPPPPPPQWER";

		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 5);
		ASSERT(results.size() > 0 && results[0].end == 14);
//		assert(false);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPPP") == 0);
	}


	void identify_longer_homopolymer_of_proline_with_small_padding() {
		std::string query = "PPPPP";
		std::string sequence = "QWERPPPPPPPPPPQWER";

		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 5);
		ASSERT(results.size() > 0 && results[0].end == 14);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPPP") == 0);
//		assert(false);
	}


	void identify_exact_compositionally_biased_fragment() {
		std::string query = "KAERQREKKKELEREELWKKLEELKLKKALEKQNSA";
		std::string sequence = "MSSSSPPAGAASAAISASEKVDGFTRKSVRKAQRQKRSQGSSQFRSQGSQAELHPLPQLKDATSNEQQELFCQKLQQCCILFDFMDSVSDLKSKEIKRATLNELVEYVSTNRGVIVESAYSDIVKMISANIFRTLPPSDNPDFDPEEDEPTLEASWPHIQLVYEFFLRFLESPDFQPSIAKRYIDQKFVQQLLELFDSEDPRERDFLKTVLHRIYGKFLGLRAFIRKQINNIFLRFIYETEHFNGVAELLEILGSIINGFALPLKAEHKQFLMKVLIPMHTAKGLALFHAQLAYCVVQFLEKDTTLTEPVIRGLLKFWPKTCSQKEVMFLGEIEEILDVIEPTQFKKIEEPLFKQISKCVSSSHFQVAERALYFWNNEYILSLIEENIDKILPIMFASLYKISKEHWNPTIVALVYNVLKTLMEMNGKLFDDLTSSYKAERQREKKKELEREELWKKLEELKLKKALEKQNSAYNMHSISSNTSSS";

		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		for (int i=0; i<results.size(); i++) {
//			DEBUG(results[i].begin);
//			DEBUG(results[i].end);
//		}
//		DEBUG(query.length());

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 438);
		ASSERT(results.size() > 0 && results[0].end == 473);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("KAERQREKKKELEREELWKKLEELKLKKALEKQNSA") == 0);
//		assert(false);
	}

	void identify_homopolymer_of_proline_extend_left() {
		std::string query = "PPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMPPPQPPPVPPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMPV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 26);
		ASSERT(results.size() > 0 && results[0].end == 42);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPQPPPVPPPPPPPPP") == 0);
	}

	void identify_homopolymer_of_proline_extend_right() {
		std::string query = "PPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMPPPPPPPPPVPPPQPPPQWERTNMPVQWERTNMPVQWERTNMPV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 26);
		ASSERT(results.size() > 0 && results[0].end == 42);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPPVPPPQPPP") == 0);
	}

	void identify_shorter_homopolymer_of_proline() {
		std::string query =                              "PPPPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMPV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);
//		DEBUG(sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1));

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 28);
		ASSERT(results.size() > 0 && results[0].end == 36);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);
//		assert(false);
	}

	void identify_shorter_homopolymer_of_proline_begin() {
		std::string query =  "PPPPPPPPPPP";
		std::string sequence = "PPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMQVQWERTNMPVQWERTNMPVQWERTNMQV";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);
//		DEBUG(sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1));

		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 1);
		ASSERT(results.size() > 0 && results[0].end == 9);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);
	}

	void identify_shorter_homopolymer_of_proline_end() {
		std::string query =                                                          "PPPPPPPPPPP";
		std::string sequence = "QWERTNMPVQWERTNMPVQWERTNMQVQWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPP";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);
		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 55);
		ASSERT(results.size() > 0 && results[0].end == 63);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);

//		assert(false);
	}

	void identify_in_shorter_sequence_than_query() {
		std::string query =    "PPPPPPPPPPP";
		std::string sequence = "PPPPPPPPP";
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);
		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 1);
		ASSERT(results.size() > 0 && results[0].end == 9);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("PPPPPPPPP") == 0);

//		assert(false);
	}

	void identify_real_sequence_mgg_motif() {
		std::string query =    "MGGMGGMGGMGGM";
		std::string sequence = "MSIMRRILCLAVVIFIINDVSSQGLGNNKNWKKNGMSLSSPGNKKPTGNNAVPQKSKMNNMNQNSLSQPKRSSPPGNSMYNMANQGPMGMMGGFGMGMNNKQMREFMIARRTHGVSPFLKKKICHMAKVAPPVNGQMPSPPQLYAQGFKIRRIGKWFSQDLDWSEGVAMCHNKEMEHRGCEKTPSSKWGRMFPGMGGMGGMGGMGGMMMGNRPMASCDVTKPNSCGNPALMKCSKYHKDRFGMPVCCATSEMTANQLENMGF";
/*
MSIMRRILCLAVVIFIINDVSSQGLGNNKNWKKNGMSLSSPGNKKPTGNNAVPQKSKMNNMNQNSLSQPKRSSPPGNSMYNMANQGPMGMMGGFGMGMNNKQMREFMIARRTHGVSPFLKKKICHMAKVAPPVNGQMPSPPQLYAQGFKIRRIGKWFSQDLDWSEGVAMCHNKEMEHRGCEKTPSSKWGRMFPGMGGMGGMGGMGGMMMGNRPMASCDVTKPNSCGNPALMKCSKYHKDRFGMPVCCATSEMTANQLENMGF";
*/
		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);
//		DEBUG(sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1));
//		DEBUG(results[1].begin);
//		DEBUG(results[1].end);
//		DEBUG(sequence.substr(results[1].begin - 1, results[1].end - results[1].begin + 1));
		ASSERT(results.size() == 2);
		ASSERT(results.size() > 0 && results[0].begin == 89);
		ASSERT(results.size() > 0 && results[0].end == 97);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("GMMGGFGMG") == 0);
		ASSERT(results.size() > 1 && results[1].begin == 194);
		ASSERT(results.size() > 1 && results[1].end == 210);
		ASSERT(results.size() > 1 && sequence.substr(results[1].begin - 1, results[1].end - results[1].begin + 1).compare("GMGGMGGMGGMGGMMMG") == 0);
	}

	void identify_real_sequence_rg_motif() {
		std::string query =    "RGRGRGRGRG";
		std::string sequence = "NVVTVNGRGRGRGRGRGRGLQRQKSADNTPASSPFAFRPFSLDSNEPTP";

		SimiComp sc;

		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
//		DEBUG(results[0].begin);
//		DEBUG(results[0].end);
		ASSERT(results.size() == 1);
		ASSERT(results.size() > 0 && results[0].begin == 7);
		ASSERT(results.size() > 0 && results[0].end == 18);
		ASSERT(results.size() > 0 && sequence.substr(results[0].begin - 1, results[0].end - results[0].begin + 1).compare("GRGRGRGRGRGR") == 0);
//		assert(false);
	}


	void identify_shorter_hit_match() {
		std::string query =    "AAAAAAAAAAAAAAAAAAAA";
		std::string sequence = "AAAAAAAAAAAAAAAAA";

		SimiComp sc;
		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

//		DEBUG(results.size());
		ASSERT(results.size() == 1);
//		assert(false);
	}


	void identify_shorter_hit_different() {
		std::string query =    "AAAAAAAAAAAAAAAAAAAA";
		std::string sequence = "CCCCCCCCCCCCCCCCC";

		SimiComp sc;
		std::vector<identification_result_t> results = sc.identify(query, sequence, SCORE_THRESHOLD, RELATIVE_THRESHOLD);

		ASSERT(results.size() == 0);
	}


	void contain_motif_with_similar_composition_true() {
		std::string query =    "AAAAAAAAAAA";
		std::string sequence = "MSIMRRILCLAVVIFIINDVSSQGLGNNKNWKKNGMSLSSPGNKKPTGNNAVPQKSKMNNMNQNAAAAAAAAAAASLSQPKRSSPPGNSMYNMANQGPMGMMGGFGMGMNNKQMREFMIARRTHGVSPFLKKKICHMAKVAPPVNGQMPSPPQLYAQGFKIRRIGKWFSQDLDWSEGVAMCHNKEMEHRGCEKTPSSKWGRMFPGMGGMGGMGGMGGMMMGNRPMASCDVTKPNSCGNPALMKCSKYHKDRFGMPVCCATSEMTANQLENMGF";

		SimiComp sc;
		bool contain = sc.contain_similar_fragment(query, sequence, SCORE_THRESHOLD);

		ASSERT(contain == true);
	}


	void contain_motif_with_similar_composition_false() {
		std::string query =    "AAAAAAAAAAA";
		std::string sequence = "MSIMRRILCLAVVIFIINDVSSQGLGNNKNWKKNGMSLSSPGNKKPTGNNAVPQKSKMNNMNQNSLSQPKRSSPPGNSMYNMANQGPMGMMGGFGMGMNNKQMREFMIARRTHGVSPFLKKKICHMAKVAPPVNGQMPSPPQLYAQGFKIRRIGKWFSQDLDWSEGVAMCHNKEMEHRGCEKTPSSKWGRMFPGMGGMGGMGGMGGMMMGNRPMASCDVTKPNSCGNPALMKCSKYHKDRFGMPVCCATSEMTANQLENMGF";

		SimiComp sc;
		bool contain = sc.contain_similar_fragment(query, sequence, SCORE_THRESHOLD);

		ASSERT(contain == false);
	}


	void TestSimiComp::run() {
		identify_homopolymer_of_proline();
		identify_homopolymer_of_proline_begin();
		identify_homopolymer_of_proline_end();
		identify_short_tandem_repeat();
		identify_two_homopolymers_of_proline();
		identify_longer_homopolymer_of_proline();
		identify_longer_homopolymer_of_proline_with_mutations();
		identify_longer_homopolymer_of_proline_with_small_padding();
		identify_longer_homopolymer_of_proline_with_small_padding_high_window_span();
		identify_shorter_homopolymer_of_proline();
		identify_in_shorter_sequence_than_query();
		identify_shorter_homopolymer_of_proline_end();
		identify_shorter_homopolymer_of_proline_begin();
		identify_homopolymer_of_proline_extend_right();
		identify_homopolymer_of_proline_extend_left();
		identify_exact_compositionally_biased_fragment();
		identify_real_sequence_mgg_motif();
		identify_real_sequence_rg_motif();
		identify_shorter_hit_match();
		identify_shorter_hit_different();
		contain_motif_with_similar_composition_true();
		contain_motif_with_similar_composition_false();

		std::cerr << "\n";
	}
}




