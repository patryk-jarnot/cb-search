/*
 * numericutils.cpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */


#include "utils/numericutils.hpp"

#include <limits>
#include <cmath>
#include <cstdio>

namespace nscsearch {

	bool number_lower_equal(float left, float right) {
		return (left - right) <= (std::numeric_limits<float>::epsilon());  // take care about float error
	}

	bool number_lower(float left, float right) {
		return (left - right) <= (-1 * std::numeric_limits<float>::epsilon());  // take care about float error
	}

	bool number_greater_equal(float left, float right) {
		return (right - left) <= (std::numeric_limits<float>::epsilon());  // take care about float error
	}

	bool number_greater(float left, float right) {
		return (right - left) <= (-1 * std::numeric_limits<float>::epsilon());  // take care about float error
	}

	bool numbers_equal(float left, float right) {
		return std::fabs(left - right) <= std::numeric_limits<float>::epsilon();  // take care about float error
	}

	bool numbers_equal(float left, float right, float precision) {
		return std::fabs(left - right) <= precision;  // take care about float error
	}

}
