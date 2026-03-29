/*
 * cbdbwriter.hpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_DAL_CBDB_CBDBWRITER_HPP_
#define NSC_SEARCH_INCLUDE_DAL_CBDB_CBDBWRITER_HPP_


#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <list>
#include "residue/scoringmatrix.hpp"


namespace cbsearch {
	class CbDbWriter {
	public:

		CbDbWriter() : file_fasta(nullptr), file_kmers(nullptr), file_idx(nullptr) {}
		virtual ~CbDbWriter() {}

		void create_files();
		void set_handlers(std::ifstream *input, std::fstream *output_mers, std::fstream *output_idx);

	private:
		std::ifstream *file_fasta;
		std::fstream *file_kmers;
		std::fstream *file_idx;
		std::map<uint16_t, std::map<uint16_t, std::list<uint32_t> > > elements;  // dimer, count, number of proteins

	};
}


#endif /* NSC_SEARCH_INCLUDE_DAL_CBDB_CBDBWRITER_HPP_ */
