/*
 * resultsitem.hpp
 *
 *  Created on: May 21, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_MODEL_RESULTSITEM_HPP_
#define NSCSEARCH_INCLUDE_MODEL_RESULTSITEM_HPP_

#include <string>

namespace nscsearch {

	struct results_fragment_t {
	public:
		int begin;
		int end;

	private:
	};


	struct results_item_t {
	public:
		results_item_t() : score(0), simi_score(0), identity(0), similarity(0) {}
		results_item_t(std::string iquery_alignment, std::string imidline_alignment, std::string ihit_alignment, std::string ihit_header, float iscore, float isimi_score, float iidentity, float isimilarity) {
			query_alignment = iquery_alignment;
			midline_alignment = imidline_alignment;
			hit_alignment = ihit_alignment;
			hit_header = ihit_header;
			score = iscore;
			simi_score = isimi_score;
			identity = iidentity;
			similarity = isimilarity;
		}

		std::string query_alignment;
		std::string midline_alignment;
		std::string hit_alignment;

		std::string hit_header;


		float score;
		float simi_score;
		float identity;
		float similarity;

		results_fragment_t fragment_info;

	private:
	};
}


#endif /* NSCSEARCH_INCLUDE_MODEL_RESULTSITEM_HPP_ */
