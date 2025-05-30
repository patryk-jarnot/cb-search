/*
 * swgapaffinitymatrices.hpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_ALIGNMENT_SW_SWGAPAFFINITYMATRICES_HPP_
#define NSC_SEARCH_INCLUDE_ALIGNMENT_SW_SWGAPAFFINITYMATRICES_HPP_


#include <string>
#include <vector>
#include "residue/scoringmatrix.hpp"


namespace nscsearch {
	class SwGapAffinityMatrices {
	public:
		enum class BestMove { NONE, MATCH, X, Y };

		SwGapAffinityMatrices();

		void set_scoring_matrix(ScoringMatrix *iscoring_matrix) { sm = iscoring_matrix; }
		void create_matrices(std::string sequence_query, std::string sequence_hit, float gap_open, float gap_extend);

		float get_m_value(int y, int x);
		float get_ix_value(int y, int x);
		float get_iy_value(int y, int x);
		void print_matrix_m();
		void print_matrix_ix();
		void print_matrix_iy();
		BestMove best_move(int i, int j, BestMove iold_move);
		float global_alignment_best_score();
		int best_score_i_pos();
		void best_score(int *oi, int *oj);
		int get_score(int i, int j);

	private:

		void fill_matrices();
		void fill_iy_first_column();
		void fill_ix_first_row();
		void fill_m_first_column();
		void fill_matrices_body();
		void print_matrix(std::vector<std::vector<float> > *matrix);

		ScoringMatrix* sm;

		const int FLOAT_MINUS_INF = -1000000.0;
		std::vector<std::vector<float> > matrix_m;
		std::vector<std::vector<float> > matrix_ix;
		std::vector<std::vector<float> > matrix_iy;

		std::string sequence_upper;
		std::string sequence_lower;
		float gap_open;
		float gap_extend;

	};
}


#endif /* NSC_SEARCH_INCLUDE_ALIGNMENT_SW_SWGAPAFFINITYMATRICES_HPP_ */
