/*
 * needlemanwunsch.cpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#include "alignment/nw/needlemanwunsch.hpp"
#include "exceptions.hpp"
#include "debug.hpp"

#include <stdio.h>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "residue/scoringmatrix.hpp"
#include "utils/stringutils.hpp"

using namespace nscsearch;
using namespace std;


void NeedlemanWunsch::save_best_alignment() {
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


void NeedlemanWunsch::align(const std::string &iquery, const std::string &ihit, float igap_open_score, float igap_extension_score) {
	query = iquery;
	hit = ihit;

	gap_open_score = igap_open_score;
	gap_extension_score = igap_extension_score;

	initialize();

//	print_matrices();

	backtracing();

	save_best_alignment();
}


void NeedlemanWunsch::initialize() {
	gam.set_scoring_matrix(&sm);
	gam.create_matrices(query, hit, gap_open_score, gap_extension_score);

	current_query_alignment = "";
	current_midline_alignment = "";
	current_hit_alignment = "";
}


char NeedlemanWunsch::midline_character(char left_residue, char right_residue) {
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


void NeedlemanWunsch::alignment_add_match(int i, int j) {
	current_query_alignment += query[j-1];
	current_midline_alignment += midline_character(query[j-1], hit[i-1]);
	current_hit_alignment += hit[i-1];
}


void NeedlemanWunsch::alignment_add_mismatch_x(int i, int j) {
	current_query_alignment += query[j-1];
	current_midline_alignment += ' ';
	current_hit_alignment += '-';
}


void NeedlemanWunsch::alignment_add_mismatch_y(int i, int j) {
	current_query_alignment += '-';
	current_midline_alignment += ' ';
	current_hit_alignment += hit[i-1];
}


void NeedlemanWunsch::backtracing() {
	int i = hit.size();
	int j = query.size();
	NwGapAffinityMatrices::BestMove move = NwGapAffinityMatrices::BestMove::NONE;

	current_query_alignment = "";
	current_midline_alignment = "";
	current_hit_alignment = "";

	while (i != 0 || j != 0) {
		move = gam.best_move(i, j, move);
		switch (move) {
		case NwGapAffinityMatrices::BestMove::MATCH:
			alignment_add_match(i, j);
			i--;
			j--;
			break;
		case NwGapAffinityMatrices::BestMove::X:
			alignment_add_mismatch_x(i, j);
			j--;
			break;
		case NwGapAffinityMatrices::BestMove::Y:
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


float NeedlemanWunsch::get_current_similarity() {
	int counter = 0;
	for (auto c : current_midline_alignment) {
		if (c != ' ') {
			counter++;
		}
	}
	return (float)counter / current_midline_alignment.size();
}


float NeedlemanWunsch::get_current_identity() {
	int counter = 0;
	for (auto c : current_midline_alignment) {
		if (c != ' ' && c != '+') {
			counter++;
		}
	}
	return (float)counter / current_midline_alignment.size();
}


void NeedlemanWunsch::print_matrices() {
	gam.print_matrix_m();
	gam.print_matrix_ix();
	gam.print_matrix_iy();
}

