/*
 * testcomplexitycalculator.cpp
 *
 *  Created on: May 4, 2023
 *      Author: pjarnot
 */


#include "tests/unittest.hpp"

#include <string>
#include <map>
#include <iostream>
#include "identification/compositioncalculator.hpp"
#include "tests/identification/testcompositioncalculator.hpp"
#include "residue/scoringmatrix.hpp"
#include "utils/numericutils.hpp"


namespace nscsearch {

	void TestCompositionCalculator::initialize_data() {

	}

	void TestCompositionCalculator::count_residues_homopolymer() {
		std::string sequence = "AAAAAAAAA";
		CompositionCalculator cc;

		std::map<char, int> occurrence_count_by_residues = cc.count_residues(sequence);

		ASSERT(occurrence_count_by_residues['A'] == 9);
	}

	void TestCompositionCalculator::count_residues_short_tandem_repeat() {
		std::string sequence = "EDEDEDEDEDEDE";
		CompositionCalculator cc;

		std::map<char, int> occurrence_count_by_residues = cc.count_residues(sequence);

		ASSERT(occurrence_count_by_residues['E'] == 7);
		ASSERT(occurrence_count_by_residues['D'] == 6);
	}

	void TestCompositionCalculator::count_residues_compositionally_biased() {
		std::string sequence = "GCAGPNSEAGALTAGALTAGAFAVTAGAGVAGAGVAGVGW";
		CompositionCalculator cc;

		std::map<char, int> occurrence_count_by_residues = cc.count_residues(sequence);

		ASSERT(occurrence_count_by_residues['A'] == 13);
		ASSERT(occurrence_count_by_residues['V'] == 4);
		ASSERT(occurrence_count_by_residues['W'] == 1);
	}

	void TestCompositionCalculator::count_residues_test_missing() {
		std::string sequence = "GCAGPNSEAGALTAGALTAGAFAVTAGAGVAGAGVAGVGW";
		CompositionCalculator cc;

		std::map<char, int> occurrence_count_by_residues = cc.count_residues(sequence);

		ASSERT(occurrence_count_by_residues['D'] == 0);
	}

	void TestCompositionCalculator::count_sequence_residues_homopolymer() {
		std::string sequence = "AAAAAAAAA";
		CompositionCalculator cc;

		std::vector<int> occurrence_count_by_residues = cc.count_sequence_residues(sequence);

		ASSERT(occurrence_count_by_residues[(int)MatrixResidue::A] == 9);
	}

	void TestCompositionCalculator::count_sequence_residues_short_tandem_repeat() {
		std::string sequence = "EDEDEDEDEDEDE";
		CompositionCalculator cc;

		std::vector<int> occurrence_count_by_residues = cc.count_sequence_residues(sequence);

		ASSERT(occurrence_count_by_residues[(int)MatrixResidue::E] == 7);
		ASSERT(occurrence_count_by_residues[(int)MatrixResidue::D] == 6);
	}

	void TestCompositionCalculator::count_sequence_residues_compositionally_biased() {
		std::string sequence = "GCAGPNSEAGALTAGALTAGAFAVTAGAGVAGAGVAGVGW";
		CompositionCalculator cc;

		std::vector<int> occurrence_count_by_residues = cc.count_sequence_residues(sequence);

		ASSERT(occurrence_count_by_residues[(int)MatrixResidue::A] == 13);
		ASSERT(occurrence_count_by_residues[(int)MatrixResidue::V] == 4);
		ASSERT(occurrence_count_by_residues[(int)MatrixResidue::W] == 1);
	}

	void TestCompositionCalculator::count_sequence_residues_test_missing() {
		std::string sequence = "GCAGPNSEAGALTAGALTAGAFAVTAGAGVAGAGVAGVGW";
		CompositionCalculator cc;

		std::vector<int> occurrence_count_by_residues = cc.count_sequence_residues(sequence);

		ASSERT(occurrence_count_by_residues[(int)MatrixResidue::D] == 0);
	}

	void calculate_identity_homopolymer_identical() {
		std::string sequence = "AAAAAAAAA";
		CompositionCalculator cc;

		float identity = cc.identity(sequence, sequence);

		ASSERT(numbers_equal(identity, 1));
	}

	void calculate_identity_complex_identical() {
		std::string sequence = "FDTEEYCMAV";
		CompositionCalculator cc;

		float identity = cc.identity(sequence, sequence);

		ASSERT(numbers_equal(identity, 1));
	}

	void calculate_identity_50_percent_homopolymer() {
		std::string left_sequence = "AAAAAAAAAA";
		std::string right_sequence = "AAAAADDDDD";
		CompositionCalculator cc;

		float identity = cc.identity(left_sequence, right_sequence);

		ASSERT(numbers_equal(identity, 0.5));
	}

	void calculate_identity_50_percent_complex() {
		std::string left_sequence = "FDTEEYCMAV";
		std::string right_sequence = "FDTEEQWERT";
		CompositionCalculator cc;

		float identity = cc.identity(left_sequence, right_sequence);

		ASSERT(numbers_equal(identity, 0.5));
	}

	void calculate_identity_0_percent_homopolymer() {
		std::string left_sequence = "AAAAAAAAAA";
		std::string right_sequence = "DDDDDDDDDD";
		CompositionCalculator cc;

		float identity = cc.identity(left_sequence, right_sequence);

		ASSERT(numbers_equal(identity, 0));
	}

	void calculate_identity_0_percent_complex() {
		std::string left_sequence = "FDTEEYCMAV";
		std::string right_sequence = "QWRIPSGHKL";
		CompositionCalculator cc;

		float identity = cc.identity(left_sequence, right_sequence);

		ASSERT(numbers_equal(identity, 0));
	}

	void TestCompositionCalculator::run() {
		initialize_data();

		count_residues_homopolymer();
		count_residues_short_tandem_repeat();
		count_residues_compositionally_biased();
		count_residues_test_missing();

		count_sequence_residues_homopolymer();
		count_sequence_residues_short_tandem_repeat();
		count_sequence_residues_compositionally_biased();
		count_sequence_residues_test_missing();

		calculate_identity_homopolymer_identical();
		calculate_identity_complex_identical();
		calculate_identity_50_percent_homopolymer();
		calculate_identity_50_percent_complex();
		calculate_identity_0_percent_homopolymer();
		calculate_identity_0_percent_complex();

		std::cerr << "\n";
	}
}


