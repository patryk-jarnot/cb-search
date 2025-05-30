/*
 * alignbase.hpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_ALIGNMENT_ALIGNBASE_HPP_
#define NSC_SEARCH_INCLUDE_ALIGNMENT_ALIGNBASE_HPP_

#include "residue/scoringmatrix.hpp"

#include <string>
#include <vector>

namespace nscsearch {
	struct alignment_t {
	public:
		float score;
		float similarity;
		float similarity_score;
		float identity;

		std::string query_alignment;
		std::string midline_alignment;
		std::string hit_alignment;
	};


	class AlignBase {
	public:
		virtual void align(const std::string &iquery, const std::string &ihit, float igap_open_score, float igap_extension_score) = 0;
		virtual ~AlignBase() {}

		virtual void mask_residues_except_selected_diagonal(std::vector<char> iresidues, float imask_value=0);
		virtual void set_cbr_correction(std::string iquery, float ialpha);
		virtual void set_max_score(float score) { max_score = score; }

//		virtual float get_score() { return gam.global_alignment_best_score(); }
//		virtual float get_similarity_score() { return get_score() / max_score; }
//		virtual float get_similarity();
//		virtual float get_identity();
//		virtual std::string get_query_alignment() { return query_alignment; }
//		virtual std::string get_midline_alignment() { return midline_alignment; }
//		virtual std::string get_hit_alignment() { return hit_alignment; }
		virtual std::vector<alignment_t> get_alignments() { return alignments; }

	protected:
		ScoringMatrix sm;

		float gap_open_score;
		float gap_extension_score;
		float max_score;

		std::string query;
		std::string hit;
		std::vector<alignment_t> alignments;
	};
}


#endif /* NSC_SEARCH_INCLUDE_ALIGNMENT_ALIGNBASE_HPP_ */
