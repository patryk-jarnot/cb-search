/*
 * onewayglobal.cpp
 *
 *  Created on: Dec 29, 2024
 *      Author: pjarnot
 */


#include "alignment/og/oggapaffinitymatrices.hpp"
#include "alignment/og/onewayglobal.hpp"

#include "exceptions.hpp"
#include "debug.hpp"
#include "utils/stringutils.hpp"

#include <algorithm>

using namespace nscsearch;



void OneWayGlobal::save_best_alignment() {
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


void OneWayGlobal::align(const std::string &iquery, const std::string &ihit, float igap_open_score, float igap_extension_score) {

	query = iquery;
	hit = ihit;

	gap_open_score = igap_open_score;
	gap_extension_score = igap_extension_score;

	initialize();

//	print_matrices();

	backtracing();

	save_best_alignment();
}


void OneWayGlobal::initialize() {
	gam.set_scoring_matrix(&sm);
	gam.create_matrices(query, hit, gap_open_score, gap_extension_score);

	current_query_alignment = "";
	current_midline_alignment = "";
	current_hit_alignment = "";
}


char OneWayGlobal::midline_character(char left_residue, char right_residue) {
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


void OneWayGlobal::alignment_add_match(int i, int j) {
	current_query_alignment += query[j-1];
	current_midline_alignment += midline_character(query[j-1], hit[i-1]);
	current_hit_alignment += hit[i-1];
}


void OneWayGlobal::alignment_add_mismatch_x(int i, int j) {
	current_query_alignment += query[j-1];
	current_midline_alignment += ' ';
	current_hit_alignment += '-';
}


void OneWayGlobal::alignment_add_mismatch_y(int i, int j) {
	current_query_alignment += '-';
	current_midline_alignment += ' ';
	current_hit_alignment += hit[i-1];
}


void OneWayGlobal::backtracing() {
	int j = query.size();
	int i = gam.best_score_i_pos();// hit.size();
	OgGapAffinityMatrices::BestMove move = OgGapAffinityMatrices::BestMove::NONE;

	current_query_alignment = "";
	current_midline_alignment = "";
	current_hit_alignment = "";

	while (j != 0) {
		move = gam.best_move(i, j, move);
//		DEBUG(static_cast<int>(move));
		switch (move) {
		case OgGapAffinityMatrices::BestMove::MATCH:
			alignment_add_match(i, j);
			i--;
			j--;
			break;
		case OgGapAffinityMatrices::BestMove::X:
			alignment_add_mismatch_x(i, j);
			j--;
			break;
		case OgGapAffinityMatrices::BestMove::Y:
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


float OneWayGlobal::get_current_similarity() {
	int counter = 0;
	for (auto c : current_midline_alignment) {
		if (c != ' ') {
			counter++;
		}
	}
	return (float)counter / current_midline_alignment.size();
}


float OneWayGlobal::get_current_identity() {
	int counter = 0;
	for (auto c : current_midline_alignment) {
		if (c != ' ' && c != '+') {
			counter++;
		}
	}
	return (float)counter / current_midline_alignment.size();
}


void OneWayGlobal::print_matrices() {
	gam.print_matrix_m();
	gam.print_matrix_ix();
	gam.print_matrix_iy();
}



