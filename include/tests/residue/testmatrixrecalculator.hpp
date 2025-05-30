/*
 * testmatrixrecalculation.hpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_RESIDUE_TESTMATRIXRECALCULATOR_HPP_
#define NSCSEARCH_INCLUDE_TESTS_RESIDUE_TESTMATRIXRECALCULATOR_HPP_


namespace nscsearch {

	class TestMatrixRecalculator {
	public:
		void run();

	private:
        void mask_residues_no_change();
        void mask_residues_all_except_selected_on_diagonal();
        void cbr_correction_homopolymer();
		void cbr_correction_short_tandem_repeat_perfect();
		void cbr_correction_short_tandem_repeat_imperfect();
	};
}



#endif /* NSCSEARCH_INCLUDE_TESTS_RESIDUE_TESTMATRIXRECALCULATOR_HPP_ */
