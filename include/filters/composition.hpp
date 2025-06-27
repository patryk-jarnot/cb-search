/*
 * composition.hpp
 *
 *  Created on: Jun 24, 2025
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_FILTERS_COMPOSITION_HPP_
#define NSC_SEARCH_INCLUDE_FILTERS_COMPOSITION_HPP_

#include "filters/filterbase.hpp"


namespace nscsearch {

	class CompositionFilter : FilterBase {
	public:
		virtual ~CompositionFilter() {}

		/**
		 * Documented in FilterBase.
		 */
		virtual bool process_window(std::string ifirst_window);

		/**
		 * Documented in FilterBase.
		 */
		virtual bool change_terminus_residues(char in_term_residue, char ic_term_residue);

		/**
		 * Documented in FilterBase.
		 */
		virtual void initialize_query_sequnce(std::string iquery) = 0;

	protected:


	};

}



#endif /* NSC_SEARCH_INCLUDE_FILTERS_COMPOSITION_HPP_ */
