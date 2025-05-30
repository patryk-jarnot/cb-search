/*
 * functionutils.hpp
 *
 *  Created on: May 18, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_UTILS_FUNCTIONUTILS_HPP_
#define NSCSEARCH_INCLUDE_UTILS_FUNCTIONUTILS_HPP_

#include <vector>

namespace nscsearch {

	std::vector<float> moving_average(std::vector<float> &ifunction_data, int iwindow_span);

}

#endif /* NSCSEARCH_INCLUDE_UTILS_FUNCTIONUTILS_HPP_ */
