/*
 * complexitymatrix.hpp
 *
 *  Created on: May 15, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONMATRIX_HPP_
#define NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONMATRIX_HPP_


#include <string>
#include "residue/scoringmatrix.hpp"


namespace nscsearch {

	struct matrix_pair_t {
		MatrixResidue residue_query;
		MatrixResidue residue_hit;
		float score;
	};


	class CompositionMatrix {
	public:
		void precalculations();
		void initialize_matrix(std::string sequence_query, std::string sequence_hit);
		int get_pair_count(char ileft_residue, char iright_residue);
		int get_pair_count(MatrixResidue ileft_residue, MatrixResidue iright_residue);
		int pop_pair_count(MatrixResidue ileft_residue, MatrixResidue iright_residue);
		void restore_tmp_vectors();
		void print_composition_matrix();
		void replace_hit_residue(MatrixResidue iold_residue, MatrixResidue inew_residue);
		int get_hit_residue_count(MatrixResidue iresidue);

		std::vector<matrix_pair_t> get_matrix_pairs_ordered_by_score_desc() {
			return matrix_pairs_ordered_by_score_desc;
		}


	private:
		int composition_matrix[SCORING_MATRIX_SIZE * SCORING_MATRIX_SIZE];

		std::vector<matrix_pair_t> matrix_pairs_ordered_by_score_desc;

		std::vector<int> counts_in_query_sequence;
		std::vector<int> counts_in_hit_sequence;

		std::vector<int> counts_in_query_sequence_tmp;
		std::vector<int> counts_in_hit_sequence_tmp;

		ScoringMatrix scoring_matrix;

	};

}



#endif /* NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONMATRIX_HPP_ */
