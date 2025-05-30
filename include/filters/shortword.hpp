/*
 * shortword.hpp
 *
 *  Created on: Jan 12, 2025
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_FILTERS_SHORTWORD_HPP_
#define NSC_SEARCH_INCLUDE_FILTERS_SHORTWORD_HPP_

#include <string>
#include <map>

namespace nscsearch {
	class ShortWordFilter {
	public:
		bool is_similar(std::string);
		void set_query(std::string iquery);

	private:
		std::string query;
		std::map<std::string, int> query_kmers;

	};
}


#endif /* NSC_SEARCH_INCLUDE_FILTERS_SHORTWORD_HPP_ */
