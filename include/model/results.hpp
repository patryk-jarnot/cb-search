/*
 * results.hpp
 *
 *  Created on: May 21, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_MODEL_RESULTS_HPP_
#define NSCSEARCH_INCLUDE_MODEL_RESULTS_HPP_

#include "model/resultsitem.hpp"

#include <vector>


namespace nscsearch {
	enum class SortOutputBy {NONE=0, SCORE, SIMI_SCORE, IDENTITY, SIMILARITY};
	enum class OutputFormat {HUMAN=0, JSON};

	class results_t {
	public:
		std::string query_header;
		std::vector<results_item_t> alignments;
	private:
	};
}


#endif /* NSCSEARCH_INCLUDE_MODEL_RESULTS_HPP_ */
