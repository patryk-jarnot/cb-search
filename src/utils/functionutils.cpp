/*
 * functionutils.cpp
 *
 *  Created on: May 18, 2023
 *      Author: pjarnot
 */

#include "utils/functionutils.hpp"

#include "debug.hpp"

#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

namespace nscsearch {

	std::vector<float> moving_average(std::vector<float> &ifunction_data, int ihistory_len) {
		assert(ihistory_len >= 0);
		std::vector<float> smoothed_data;

		float total = 0;
		for (size_t i=0; i<ifunction_data.size(); i++) {
			int element_old = i-ihistory_len-1;

			total += ifunction_data[i];
			if (element_old >=0) {
				total -= ifunction_data[element_old];
			}

			int window_size = ihistory_len + 1 - std::max(0, (int)(i-ihistory_len) * -1);

			float average = total / window_size;

			smoothed_data.push_back(average);
		}

		return smoothed_data;
	}
}

