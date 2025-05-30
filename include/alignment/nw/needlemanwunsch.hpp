/*
 * needlemanwunsch.hpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_NEEDLEMANWUNSCH_HPP_
#define NSCSEARCH_INCLUDE_NEEDLEMANWUNSCH_HPP_

#include "alignment/nw/nwgapaffinitymatrices.hpp"
#include "alignment/alignbase.hpp"

#include <string>
#include <vector>
#include <initializer_list>

namespace nscsearch {
	class NeedlemanWunsch : public AlignBase {
	public:
		virtual void align(const std::string &iquery, const std::string &ihit, float igap_open_score, float igap_extension_score);

		virtual void print_matrices();

	private:
		void initialize();
		void backtracing();
		void alignment_add_match(int i, int j);
		void alignment_add_mismatch_x(int i, int j);
		void alignment_add_mismatch_y(int i, int j);
		char midline_character(char left_residue, char right_residue);

		float get_current_identity();
		float get_current_similarity();

		void save_best_alignment();

		NwGapAffinityMatrices gam;

		std::string current_query_alignment;
		std::string current_midline_alignment;
		std::string current_hit_alignment;
	};
}


#endif /* NSCSEARCH_INCLUDE_NEEDLEMANWUNSCH_HPP_ */
