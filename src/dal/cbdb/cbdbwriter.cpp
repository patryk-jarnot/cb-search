/*
 * cbdbwriter.cpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */

#include "dal/cbdb/cbdbwriter.hpp"
#include "utils/fasta.hpp"
#include "utils/sequenceutils.hpp"
#include "debug.hpp"


using namespace cbsearch;
using namespace std;


void CbDbWriter::set_handlers(std::ifstream *input, std::fstream *output_mers, std::fstream *output_idx) {
	file_fasta = input;
	file_kmers = output_mers;
	file_idx = output_idx;
}


void initialize_stats_parse_seq(map<uint16_t, map<uint16_t, list<uint32_t> > > *init_stats, string *sequence, uint32_t seq_id) {
	map<uint16_t, int> kmers = count_kmers(sequence);
	for (auto it : kmers) {
		if (init_stats->find(it.first) == init_stats->end()) {
			(*init_stats)[it.first] = map<uint16_t, list<uint32_t> >();
		}
		(*init_stats)[it.first][it.second].push_back(seq_id);
	}
}


void write_seq_idx(fstream *fidx, uint32_t seq_id, uint64_t beg_pos, uint16_t len) {
//	*fidx << seq_id << beg_pos << len;
	fidx->write(reinterpret_cast<char*> (&seq_id), sizeof(seq_id));
	fidx->write(reinterpret_cast<char*> (&beg_pos), sizeof(beg_pos));
	fidx->write(reinterpret_cast<char*> (&len), sizeof(len));
}


void initialize_stats(ifstream *ifs, fstream *fidx, map<uint16_t, map<uint16_t, list<uint32_t> > > *init_stats) {
	ifs->seekg(0);
	fasta::FastaReader fasta_reader;
	fasta_reader.open_file(ifs);
	uint64_t beg_pos = 0;
	uint32_t len = 0;
	uint32_t seq_id = 1;
	while (fasta_reader.has_next_sequence()) {
		fasta::Sequence *fasta_seq = fasta_reader.read_next_sequence();
		len = fasta_reader.tellg() - beg_pos;
		write_seq_idx(fidx, seq_id, beg_pos, len);
		initialize_stats_parse_seq(init_stats, &(fasta_seq->sequence), seq_id);
		seq_id++;
		beg_pos = fasta_reader.tellg();
	}
}

// std::map<uint16_t, std::map<uint16_t, std::list<uint32_t> > > elements;
void CbDbWriter::create_files() {
//	DEBUG(".");
	initialize_stats(file_fasta, file_idx, &elements);
//	DEBUG(".");
	for (auto count_by_kmer : (elements)) {

		uint16_t kmer = count_by_kmer.first;
		file_kmers->write(reinterpret_cast<char*>(&kmer), sizeof(kmer));

		uint16_t count_size = count_by_kmer.second.size();
		file_kmers->write(reinterpret_cast<char*> (&count_size), sizeof(count_size));

		for (auto ids_by_count: count_by_kmer.second) {
			uint16_t count = (uint16_t)ids_by_count.first;
			file_kmers->write(reinterpret_cast<char*> (&count), sizeof(count));
			uint32_t id_size = ids_by_count.second.size();
			file_kmers->write(reinterpret_cast<char*> (&id_size), sizeof(id_size));

			for (auto id : ids_by_count.second) {
				uint32_t id_seq = id;
				file_kmers->write(reinterpret_cast<char*> (&id_seq), sizeof(id_seq));
			}
		}
	}
}

