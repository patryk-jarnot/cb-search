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

		CbDbReader() : files_opened(false), file_fasta(nullptr), file_kmers(nullptr), file_idx(nullptr), total_kmers(0), dimer_threshold(0) {}
		virtual ~CbDbReader();

		void load_database();
		void set_handlers(std::ifstream *input, std::fstream *output_mers, std::fstream *output_idx);
		void open_files(std::string idb_path);

		std::vector<cbsearch::Sequence> get_seqeunces(std::map<uint16_t, int> *kmers, float threshold);
		std::vector<cbsearch::Sequence> get_seqeunces(std::string *sequence, float threshold);

		void find_seqeunces(std::string *isequence, float threshold);
		Sequence get_next_sequence();
		bool has_next_sequence() { return count_by_id_iterator != count_by_id.end(); }

	private:
		bool files_opened;
		std::ifstream *file_fasta;
		std::fstream *file_kmers;
		std::fstream *file_idx;
		std::map<uint16_t, std::map<int, std::list<uint32_t> > > elements;  // dimer, count, number of proteins
		std::map<uint32_t, db_index_val_t> location_by_idx;
		std::map<uint32_t, uint32_t> count_by_id;
		std::map<uint32_t, uint32_t>::iterator count_by_id_iterator;
		int total_kmers;
		int dimer_threshold;
	};
}


#endif /* NSC_SEARCH_INCLUDE_DAL_CBDB_CBDBREADER_HPP_ */

