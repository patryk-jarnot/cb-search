/*
 * testcomplexitycalculator.hpp
 *
 *  Created on: May 4, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONCALCULATOR_HPP_
#define NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONCALCULATOR_HPP_


namespace nscsearch {
	class TestCompositionCalculator {
	public:
		void run();

	private:
		void initialize_data();

		void count_residues_homopolymer();
		void count_residues_short_tandem_repeat();
		void count_residues_compositionally_biased();
		void count_residues_test_missing();

		void count_sequence_residues_homopolymer();
		void count_sequence_residues_short_tandem_repeat();
		void count_sequence_residues_compositionally_biased();
		void count_sequence_residues_test_missing();
	};
}


#endif /* NSCSEARCH_INCLUDE_TESTS_IDENTIFICATION_TESTCOMPOSITIONCALCULATOR_HPP_ */
