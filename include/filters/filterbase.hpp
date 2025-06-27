/*
 * filterbase.hpp
 *
 *  Created on: Jun 25, 2025
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_FILTERS_FILTERBASE_HPP_
#define NSC_SEARCH_INCLUDE_FILTERS_FILTERBASE_HPP_


#include <string>
#include <map>

namespace nscsearch {
	class FilterBase {
	public:
		virtual ~FilterBase() {};

		/**
		 * Initializes statistics with a given window.
		 *
		 * @param ifirst_window Substring containing a window of a query length.
		 * @return true if sequence contain similar region or false otherwise
		 */
		virtual bool process_window(std::string ifirst_window) = 0;

		/**
		 * Update statistics by removing residues that will leave the window and applying one that approach it.
		 *
		 * @param in_term_residue Residue that is at n terminus of the window.
		 * @param ic_term_residue Residue that is at c terminus of the window.
		 * @return true if sequence contain similar region or false otherwise
		 */
		virtual bool change_terminus_residues(char in_term_residue, char ic_term_residue) = 0;

		/**
		 * Initializes internal filter structures with full query sequence.
		 *
		 * @param iquery full query sequence.
		 */
		virtual void initialize_query_sequnce(std::string iquery) = 0;

	private:

	};
}


#endif /* NSC_SEARCH_INCLUDE_FILTERS_FILTERBASE_HPP_ */
