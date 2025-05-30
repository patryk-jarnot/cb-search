/*
 * fragmentextender.hpp
 *
 *  Created on: May 19, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_IDENTIFICATION_FRAGMENTEXTENDER_HPP_
#define NSCSEARCH_INCLUDE_IDENTIFICATION_FRAGMENTEXTENDER_HPP_

#include <vector>

namespace nscsearch {

	class FragmentExtender {
	public:
		void extend_fragment(int *iobegin, int *ioend, std::vector<float> &smoothed_scores);

	private:

	};

}


#endif /* NSCSEARCH_INCLUDE_IDENTIFICATION_FRAGMENTEXTENDER_HPP_ */
