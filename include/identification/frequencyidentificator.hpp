/*
 * similarcomplexity.hpp
 *
 *  Created on: May 4, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONIDENTIFICATOR_HPP_
#define NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONIDENTIFICATOR_HPP_


#include <vector>
#include <string>


namespace nscsearch {
	struct identification_result_t {
		identification_result_t(int ibegin, int iend) : begin(ibegin), end(iend) {}
		identification_result_t() : begin(0), end(0) {}
		int begin;
		int end;
	};

	class FrequencyIdentificator {
	public:
		std::vector<identification_result_t> identify(std::string iquery, std::string ihit,
				float ifrequency_diff_threshold);

	private:


	};
}


#endif /* NSCSEARCH_INCLUDE_IDENTIFICATION_COMPOSITIONIDENTIFICATOR_HPP_ */
