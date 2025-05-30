/*
 * gapaffinitymatrix.hpp
 *
 *  Created on: Mar 27, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_ALIGNMENT_NWGAPAFFINITYMATRICES_HPP_
#define NSCSEARCH_INCLUDE_ALIGNMENT_NWGAPAFFINITYMATRICES_HPP_

#include <string>
#include <vector>
#include "residue/scoringmatrix.hpp"


namespace nscsearch {
	class NwGapAffinityMatrices {
	public:
		enum class BestMove { NONE, MATCH, X, Y };

		NwGapAffinityMatrices();

		void set_scoring_matrix(ScoringMatrix *iscoring_matrix) { sm = iscoring_matrix; }
		void create_matrices(std::string sequence_upper, std::string sequence_lower, float gap_open, float gap_extend);

		float get_m_value(int y, int x);
		float get_ix_value(int y, int x);
		float get_iy_value(int y, int x);
		void print_matrix_m();
		void print_matrix_ix();
		void print_matrix_iy();
		BestMove best_move(int i, int j, BestMove iold_move);
		float global_alignment_best_score();

	private:

		void fill_matrices();
		void fill_iy_first_column();
		void fill_ix_first_row();
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


#endif /* NSCSEARCH_INCLUDE_ALIGNMENT_NWGAPAFFINITYMATRICES_HPP_ */
