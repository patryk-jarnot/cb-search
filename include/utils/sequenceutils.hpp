/*
 * sequenceutils.hpp
 *
 *  Created on: Mar 29, 2026
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_UTILS_SEQUENCEUTILS_HPP_
#define NSC_SEARCH_INCLUDE_UTILS_SEQUENCEUTILS_HPP_

#include <string>
#include <map>
#include <cstdint>

namespace cbsearch {
	std::map<uint16_t, int> count_kmers(std::string *sequence);
}


#endif /* NSC_SEARCH_INCLUDE_UTILS_SEQUENCEUTILS_HPP_ */
