/*
 * cbdbwriter.cpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */

#include "dal/cbdb/cbdbwriter.hpp"
#include "utils/fasta.hpp"
#include "debug.hpp"

using namespace cbsearch;
using namespace std;


void CbDbWriter::set_handlers(std::ifstream *input, std::fstream *output_mers, std::fstream *output_idx) {
	file_fasta = input;
	file_kmers = output_mers;
	file_idx = output_idx;
}


map<uint16_t, int> calculate_kmers(string *sequence) {
	map<uint16_t, int> kmers;
	for (size_t i=0; i<sequence->size()-1; i++) {
		uint16_t kmer = ((uint16_t)(*sequence)[i] << 8) | (uint16_t)(*sequence)[i+1];
		if (kmers.find(kmer) == kmers.end()) {
			kmers[kmer] = 1;
		}
		else {
			kmers[kmer]++;
		}
	}
	return kmers;
}


void initialize_stats_parse_seq(map<uint16_t, map<int, int> > *init_stats, string *sequence) {
	map<uint16_t, int> kmers = calculate_kmers(sequence);
	for (auto it : kmers) {
		if (init_stats->find(it.first) == init_stats->end()) {
			(*init_stats)[it.first] = map<int, int>();
			(*init_stats)[it.first][it.second] = 1;
		}
		else {
			(*init_stats)[it.first][it.second]++;
		}
	}
}


void write_seq_idx(fstream *fidx, uint32_t seq_id, uint64_t beg_pos, uint16_t len) {
//	*fidx << seq_id << beg_pos << len;
	fidx->write(reinterpret_cast<char*> (&seq_id), sizeof(seq_id));
	fidx->write(reinterpret_cast<char*> (&beg_pos), sizeof(beg_pos));
	fidx->write(reinterpret_cast<char*> (&len), sizeof(len));
}


void initialize_stats(ifstream *ifs, fstream *fidx, map<uint16_t, map<int, int> > *init_stats) {
	ifs->seekg(0);
	fasta::FastaReader fasta_reader;
	fasta_reader.open_file(ifs);
	uint64_t beg_pos = 0;
	uint32_t len = 0;
	uint32_t seq_id = 1;
	while (fasta_reader.has_next_sequence()) {
		len = fasta_reader.tellg() - beg_pos;
		fasta::Sequence *fasta_seq = fasta_reader.read_next_sequence();
		write_seq_idx(fidx, seq_id, beg_pos, len);
		initialize_stats_parse_seq(init_stats, &(fasta_seq->sequence));
		seq_id++;
	}
}


void CbDbWriter::initialize_file() {
	DEBUG(".");
	initialize_stats(file_fasta, file_idx, &init_stats);
	DEBUG(".");
	for (auto kmers : (init_stats)) {
//		*file_kmers << kmers.first[0] << kmers.first[1] << (uint16_t)kmers.second.size();

		uint16_t len = (uint16_t)kmers.second.size();
		uint16_t kmer = kmers.first;

//		file_kmers->write(&(kmers.first[0]), sizeof(char));
//		file_kmers->write(&(kmers.first[1]), sizeof(char));
		file_kmers->write(reinterpret_cast<char*>(&kmer), sizeof(kmer));
		file_kmers->write(reinterpret_cast<char*> (&len), sizeof(len));
	}

	DEBUG(".");
	uint64_t id_pos = file_kmers->tellp();
	for (auto kmers : (init_stats)) {
		for (auto seqc_by_kmerc : kmers.second) {
			id_pos += sizeof(uint16_t) + sizeof(uint64_t);
		}
	}

	DEBUG(".");
	for (auto kmers : (init_stats)) {
		for (auto seqc_by_kmerc : kmers.second) {
			uint32_t key = (((uint32_t)(kmers.first) << 16) | seqc_by_kmerc.first);
			uint16_t kmerc = (uint16_t)seqc_by_kmerc.first;
			file_kmers->write(reinterpret_cast<char*>(&kmerc), sizeof(kmerc));
			file_kmers->write(reinterpret_cast<char*>(&id_pos), sizeof(id_pos));

			pos_by_kmer_and_quantity[key] = id_pos;
			id_pos += seqc_by_kmerc.second * sizeof(uint64_t);
		}
	}
	uint64_t zero = 0;
	for (uint64_t i=file_kmers->tellg(); i<=id_pos; i+=sizeof(zero)) {
		file_kmers->write(reinterpret_cast<char*> (&zero), sizeof(zero));
	}
	DEBUG(".");
}


void fill_the_file_parse_seq(uint32_t seq_id, string *sequence, fstream *file_kmers, std::map<uint32_t, uint64_t> *pos_by_kmer_and_quantity) {
	map<uint16_t, int> kmers = calculate_kmers(sequence);

	for (auto kmer : kmers) {
		uint32_t key = (((uint32_t)(kmer.first) << 16) | kmer.second);
		file_kmers->seekp((*pos_by_kmer_and_quantity)[key]);
//		*file_kmers << seq_id;
		file_kmers->write(reinterpret_cast<char*> (&seq_id), sizeof(seq_id));
		(*pos_by_kmer_and_quantity)[key] += sizeof(seq_id);
	}
}


void CbDbWriter::fill_the_file() {
	file_fasta->seekg(0);
	fasta::FastaReader fasta_reader;
	fasta_reader.open_file(dynamic_cast<istream*>(file_fasta));

	uint32_t seq_id = 1;
	while (fasta_reader.has_next_sequence()) {
		fasta::Sequence *fasta_seq = fasta_reader.read_next_sequence();
		fill_the_file_parse_seq(seq_id, &(fasta_seq->sequence), file_kmers, &pos_by_kmer_and_quantity);
		seq_id++;
	}
}

