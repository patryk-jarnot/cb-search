/*
 * smithwaterman.hpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_ALIGNMENT_SW_SMITHWATERMAN_HPP_
#define NSC_SEARCH_INCLUDE_ALIGNMENT_SW_SMITHWATERMAN_HPP_


#include "alignment/alignbase.hpp"
#include "alignment/sw/swgapaffinitymatrices.hpp"

namespace nscsearch {

	class SmithWaterman : public AlignBase {
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

		SwGapAffinityMatrices gam;

		std::string current_query_alignment;
		std::string current_midline_alignment;
		std::string current_hit_alignment;
	};
}


#endif /* NSC_SEARCH_INCLUDE_ALIGNMENT_SW_SMITHWATERMAN_HPP_ */
