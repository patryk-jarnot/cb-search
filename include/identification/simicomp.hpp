/*
 * simicomp.hpp
 *
 *  Created on: Nov 1, 2024
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_IDENTIFICATION_SIMICOMP_HPP_
#define NSC_SEARCH_INCLUDE_IDENTIFICATION_SIMICOMP_HPP_

/* ALGORITHM DESIGN
 * Input: query, database_sequence, similarity threshold.
 * 1. Calculate query composition as an array. How to map letters to numbers?
 * 2. Calculate first window composition.
 * 3. For each consecutive residue:
 * 		1. Increase count of new residue.
 * 		2. Check and increase current score if applicable.
 * 		3. Decrease count of old residue - residue that become out of the window.
 * 		4. Check and decrease current score if applicable.
 * 		5. Update maximal score.
 * 4. Exit if maximal score below threshold
 * 5. Select regions above score threshold.
 * 6. Extend and shrink found regions.
 * Output: Regions with similar composition. Regions are defined by their boundaries and returned as a list of them.
 */

#include <vector>
#include <string>


namespace nscsearch {
	struct identification_result_t {
		identification_result_t(int ibegin, int iend, float iscore) : begin(ibegin), end(iend), score(iscore) {}
		identification_result_t(int ibegin, int iend) : begin(ibegin), end(iend), score(0) {}
		identification_result_t() : begin(0), end(0), score(0) {}
		int begin;
		int end;
		float score;
	};

	class SimiComp {
	public:
		SimiComp();
		std::vector<identification_result_t> identify(std::string &iquery, std::string &ihit,
				float ifrequency_diff_threshold, float irelative_threshold);
		bool contain_similar_fragment(std::string &iquery, std::string &ihit, float ifrequency_diff_threshold);
		void encode_string(std::string &iraw_string, std::vector<char> &oencoded_string);
		void similarity_score_per_window(std::vector<float> &oscores, std::vector<char> &iquery, std::vector<char> &ihit);

	private:
		char mapper[128] = {0};

	};
}


#endif /* NSC_SEARCH_INCLUDE_IDENTIFICATION_SIMICOMP_HPP_ */
