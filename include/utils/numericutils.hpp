/*
 * numericutils.hpp
 *
 *  Created on: Apr 19, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_UTILS_NUMERICUTILS_HPP_
#define NSCSEARCH_INCLUDE_UTILS_NUMERICUTILS_HPP_


#include <limits>


namespace nscsearch {
	bool number_lower_equal(float left, float right);
	bool number_lower(float left, float right);
	bool number_greater_equal(float left, float right);
	bool number_greater(float left, float right);

	bool numbers_equal(float left, float right);
	bool numbers_equal(float left, float right, float precision);
}


#endif /* NSCSEARCH_INCLUDE_UTILS_NUMERICUTILS_HPP_ */
