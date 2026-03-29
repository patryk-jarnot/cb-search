/*
 * cbdbreader.hpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_DAL_CBDB_CBDBREADER_HPP_
#define NSC_SEARCH_INCLUDE_DAL_CBDB_CBDBREADER_HPP_


#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <list>
#include "residue/scoringmatrix.hpp"
#include "model/sequence.hpp"


namespace cbsearch {
	struct db_index_val_t {
//		uint32_t idx;
		uint64_t pos;
		uint16_t len;
	};
	class CbDbReader {
	public:

		CbDbReader() : file_fasta(nullptr), file_kmers(nullptr), file_idx(nullptr) {}
		virtual ~CbDbReader() {}

		void load_database();
		void set_handlers(std::ifstream *input, std::fstream *output_mers, std::fstream *output_idx);

		std::vector<cbsearch::Sequence> get_seqeunces(std::map<uint16_t, int> *kmers, float threshold);

	private:
		std::ifstream *file_fasta;
		std::fstream *file_kmers;
		std::fstream *file_idx;
		std::map<uint16_t, std::map<int, std::list<uint32_t> > > elements;  // dimer, count, number of proteins
		std::map<uint32_t, db_index_val_t> location_by_idx;

	};
}


#endif /* NSC_SEARCH_INCLUDE_DAL_CBDB_CBDBREADER_HPP_ */

