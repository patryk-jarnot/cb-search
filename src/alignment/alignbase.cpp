/*
 * alignbase.cpp
 *
 *  Created on: Dec 30, 2024
 *      Author: pjarnot
 */

#include "alignment/alignbase.hpp"

using namespace nscsearch;


void AlignBase::mask_residues_except_selected_diagonal(std::vector<char> iresidues, float imask_value) {
	sm.mask_residues_except_diagonal(iresidues, imask_value);
}


void AlignBase::set_cbr_correction(std::string iquery, float ialpha) {
	sm.apply_cbr_correction(iquery, ialpha);
}

