/*
 * kmer.hpp
 *
 *  Created on: Jun 24, 2025
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_FILTERS_KMER_HPP_
#define NSC_SEARCH_INCLUDE_FILTERS_KMER_HPP_

#include "filters/filterbase.hpp"


namespace nscsearch {

	class KmerFilter : FilterBase {
	public:
		virtual ~KmerFilter() {}

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
		virtual void initialize_query_sequnce(std::string iquery);

		virtual void set_acceptance_threshold(float ithreshold) { acceptance_threshold = ithreshold; }

		bool contain_similar_fragment(std::string ihit);
		virtual bool contain_similar_fragment(std::string iquery, std::string ihit, float iacceptance_threshold);

		float get_similarity() { return (float)similar_kmers/window_length;}

	protected:
		char prev_n_term_residue;
		char prev_c_term_residue;
//		std::map<std::string, int> count_by_kmer;
		static const int KMER_ARRAY_SIZE = 26;
		char query_count_by_kmer[KMER_ARRAY_SIZE][KMER_ARRAY_SIZE] = { 0 };
		char hit_count_by_kmer[KMER_ARRAY_SIZE][KMER_ARRAY_SIZE] = { 0 };
		float acceptance_threshold;
		int window_length;
		int similar_kmers;

	};

}


#endif /* NSC_SEARCH_INCLUDE_FILTERS_KMER_HPP_ */
