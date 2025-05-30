/*
 * sequencefrequency.hpp
 *
 *  Created on: Dec 1, 2023
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_IDENTIFICATION_SEQUENCEFREQUENCY_HPP_
#define NSC_SEARCH_INCLUDE_IDENTIFICATION_SEQUENCEFREQUENCY_HPP_

#include <string>
#include <vector>
#include <map>

namespace nscsearch {

	class SequenceFrequency {
	public:
		std::vector<float> calculate_frequency_similarity_for_hit_over_query_window(std::string iquery, std::string ihit);

	private:

	};

}


#endif /* NSC_SEARCH_INCLUDE_IDENTIFICATION_SEQUENCEFREQUENCY_HPP_ */
