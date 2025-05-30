/*
 * smithwaterman.cpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */




#include "alignment/sw/swgapaffinitymatrices.hpp"
#include "alignment/sw/smithwaterman.hpp"

#include "exceptions.hpp"
#include "debug.hpp"
#include "utils/stringutils.hpp"

#include <algorithm>

using namespace nscsearch;



void SmithWaterman::save_best_alignment() {
	alignment_t alignment;
	alignment.query_alignment = current_query_alignment;
	alignment.midline_alignment = current_midline_alignment;
	alignment.hit_alignment = current_hit_alignment;

	alignment.similarity = get_current_similarity();
	alignment.identity = get_current_identity();
	alignment.score = gam.global_alignment_best_score();
	alignment.similarity_score = alignment.score / max_score;
	alignments.clear();
	alignments.push_back(alignment);
}


void SmithWaterman::align(const std::string &iquery, const std::string &ihit, float igap_open_score, float igap_extension_score) {

	query = iquery;
	hit = ihit;

	gap_open_score = igap_open_score;
	gap_extension_score = igap_extension_score;

	initialize();

//	print_matrices();

	backtracing();

	save_best_alignment();
}


void SmithWaterman::initialize() {
	gam.set_scoring_matrix(&sm);
	gam.create_matrices(query, hit, gap_open_score, gap_extension_score);

	current_query_alignment = "";
	current_midline_alignment = "";
	current_hit_alignment = "";
}


char SmithWaterman::midline_character(char left_residue, char right_residue) {
	if (left_residue == right_residue) {
		return right_residue;
	}
	else if (sm.get_score(left_residue, right_residue) > 0) {
		return '+';
	}
	else {
		return ' ';
	}
}


void SmithWaterman::alignment_add_match(int i, int j) {
	current_query_alignment += query[j-1];
	current_midline_alignment += midline_character(query[j-1], hit[i-1]);
	current_hit_alignment += hit[i-1];
}


void SmithWaterman::alignment_add_mismatch_x(int i, int j) {
	current_query_alignment += query[j-1];
	current_midline_alignment += ' ';
	current_hit_alignment += '-';
}


void SmithWaterman::alignment_add_mismatch_y(int i, int j) {
	current_query_alignment += '-';
	current_midline_alignment += ' ';
	current_hit_alignment += hit[i-1];
}


void SmithWaterman::backtracing() {
	int i, j;
	gam.best_score(&i, &j);
	SwGapAffinityMatrices::BestMove move = SwGapAffinityMatrices::BestMove::NONE;

	current_query_alignment = "";
	current_midline_alignment = "";
	current_hit_alignment = "";

	while (gam.get_score(i, j) != 0) {
		move = gam.best_move(i, j, move);
//		DEBUG(static_cast<int>(move));
		switch (move) {
		case SwGapAffinityMatrices::BestMove::MATCH:
			alignment_add_match(i, j);
			i--;
			j--;
			break;
		case SwGapAffinityMatrices::BestMove::X:
			alignment_add_mismatch_x(i, j);
			j--;
			break;
		case SwGapAffinityMatrices::BestMove::Y:
			alignment_add_mismatch_y(i, j);
			i--;
			break;
		default:
			NotImplemented(__FILE__, __LINE__);
		}
	}
	current_query_alignment = reverse_str(current_query_alignment);
	current_midline_alignment = reverse_str(current_midline_alignment);
	current_hit_alignment = reverse_str(current_hit_alignment);
}


float SmithWaterman::get_current_similarity() {
	int counter = 0;
	for (auto c : current_midline_alignment) {
		if (c != ' ') {
			counter++;
		}
	}
	return (float)counter / current_midline_alignment.size();
}


float SmithWaterman::get_current_identity() {
	int counter = 0;
	for (auto c : current_midline_alignment) {
		if (c != ' ' && c != '+') {
			counter++;
		}
	}
	return (float)counter / current_midline_alignment.size();
}


void SmithWaterman::print_matrices() {
	gam.print_matrix_m();
	gam.print_matrix_ix();
	gam.print_matrix_iy();
}



