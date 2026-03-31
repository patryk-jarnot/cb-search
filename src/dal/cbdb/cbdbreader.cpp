/*
 * cbdbreader.cpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */

#include "dal/cbdb/cbdbreader.hpp"
#include "model/sequence.hpp"
#include "utils/sequenceutils.hpp"

#include "debug.hpp"

#include <algorithm>
#include <thread>
#include <chrono>


using namespace std;
using namespace cbsearch;
using namespace nscsearch;


void CbDbReader::set_handlers(std::ifstream *input_fasta, std::fstream *input_mers, std::fstream *input_idx) {
	file_fasta = input_fasta;
	file_kmers = input_mers;
	file_idx = input_idx;
}


void load_idx(std::fstream *file_idx, std::map<uint32_t, db_index_val_t> *location_by_idx) {
	file_idx->seekg(0);
	uint32_t seq_id = 1;
	uint32_t pos = 1;
	uint32_t len = 1;
	while (true) {
		file_idx->read(reinterpret_cast<char*>(&seq_id), sizeof(uint32_t));
		file_idx->read(reinterpret_cast<char*>(&pos), sizeof(uint64_t));
		file_idx->read(reinterpret_cast<char*>(&len), sizeof(uint16_t));

		if (file_idx->eof()) {
			break;
		}
//
//		DEBUG("seq_id: " << seq_id);
//		DEBUG("val.pos: " << val.pos);
//		DEBUG("val.len: " << val.len);
//
//		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		(*location_by_idx)[seq_id] = {pos, len};
	}
}


void load_kmers(std::fstream *file_kmers, std::map<uint16_t, std::map<int, std::list<uint32_t> > > *elements) {
	uint16_t kmer;
	uint16_t count_size;
	uint16_t count;
	uint32_t id_size;
	uint32_t id;

	while (true) {
//		DEBUG(file_kmers->tellg());
		// read kmer
		file_kmers->read(reinterpret_cast<char*>(&kmer), sizeof(kmer));
		if (file_kmers->eof()) {
			break;
		}
		if (elements->find(kmer) == elements->end()) {
			(*elements)[kmer] = map<int, list<uint32_t> >();
		}

		// read count_size
		file_kmers->read(reinterpret_cast<char*>(&count_size), sizeof(count_size));
		for (size_t c=0; c<count_size; c++) {
//			DEBUG((char)(kmer>>8));
//			DEBUG((char)kmer);
			// read count
			file_kmers->read(reinterpret_cast<char*>(&count), sizeof(count));
			if ((*elements)[kmer].find(count) == (*elements)[kmer].end()) {
				(*elements)[kmer][count] = list<uint32_t>();
			}
//			DEBUG(count);
			// read id_size
			file_kmers->read(reinterpret_cast<char*>(&id_size), sizeof(id_size));
//			DEBUG(id_size);
			for (size_t i=0; i<id_size; i++) {
				// read id
				file_kmers->read(reinterpret_cast<char*>(&id), sizeof(id));
				(*elements)[kmer][count].push_back(id);
			}
		}
		if (file_kmers->eof()) {
			break;
		}
	}
}


void CbDbReader::load_database() {
	load_idx(file_idx, &location_by_idx);
	load_kmers(file_kmers, &elements);
}


cbsearch::Sequence parse_sequence(string seq_fasta) {
//	DEBUG(seq_fasta)
	auto nl_it = seq_fasta.find('\n');
	string header = seq_fasta.substr(0, nl_it);
	string sequence = string(seq_fasta.begin() + nl_it+1, seq_fasta.end());
	sequence.erase(std::remove(sequence.begin(), sequence.end(), '\n'), sequence.end());
//	DEBUG(header)
//	DEBUG(sequence)
	return cbsearch::Sequence(header, sequence);
}

void CbDbReader::find_seqeunces(std::string *isequence, float threshold) {
	std::map<uint16_t, int> kmers = count_kmers(isequence);
	dimer_threshold = threshold;
	total_kmers = 0;
	for (auto kmer_count : kmers) {
		total_kmers += kmer_count.second;
	}

	int current_count = 0;
	count_by_id = map<uint32_t, uint32_t>();
	for (auto kmer_count : kmers) {
		current_count += kmer_count.second;
		for (int i=kmer_count.second; i>0; i--) {
			for (auto prot_id : elements[kmer_count.first][i]) {
				if (count_by_id.find(prot_id) == count_by_id.end() && ((1.0-(float)current_count/total_kmers) < threshold)) {
					count_by_id[prot_id] = i;
				}
				else if (((1.0-(float)current_count/total_kmers) + ((float)count_by_id[prot_id]/total_kmers)) > threshold) {
					auto it = count_by_id.find(prot_id);
					count_by_id.erase(it);
				}
				else {
					count_by_id[prot_id] += i;
				}
			}
		}
	}
	count_by_id_iterator = count_by_id.begin();
}

Sequence CbDbReader::get_next_sequence() {
	while (count_by_id_iterator != count_by_id.end()) {
		if (((float)(*count_by_id_iterator).second/total_kmers) > dimer_threshold) {
			db_index_val_t loc = location_by_idx[(*count_by_id_iterator).first];
			string seq(loc.len, '.');
			file_fasta->seekg(loc.pos, file_fasta->beg);
			file_fasta->read(&(seq[0]), loc.len);
			count_by_id_iterator++;
			return parse_sequence(seq);
		}
		else {
			count_by_id_iterator++;
		}
	}
	return Sequence("", "");
}

std::vector<Sequence> CbDbReader::get_seqeunces(std::string *isequence, float threshold) {
	std::map<uint16_t, int> kmers = count_kmers(isequence);
	return get_seqeunces(&kmers, threshold);
}

std::vector<Sequence> CbDbReader::get_seqeunces(std::map<uint16_t, int> *kmers, float threshold) {
	int total_kmers = 0;
	for (auto kmer_count : *kmers) {
		total_kmers += kmer_count.second;
	}

	int current_count = 0;
	map<uint32_t, uint32_t> count_by_id;
	for (auto kmer_count : *kmers) {
//		DEBUG("kmer: " << (char)(kmer_count.first >> 8) << (char)kmer_count.first);
//		DEBUG("count: " << kmer_count.second);
		current_count += kmer_count.second;
		for (int i=kmer_count.second; i>0; i--) {
			for (auto prot_id : elements[kmer_count.first][i]) {
				if (count_by_id.find(prot_id) == count_by_id.end() && ((1.0-(float)current_count/total_kmers) < threshold)) {
					count_by_id[prot_id] = i;
				}
				else if (((1.0-(float)current_count/total_kmers) + ((float)count_by_id[prot_id]/total_kmers)) > threshold) {
					auto it = count_by_id.find(prot_id);
					count_by_id.erase(it);
				}
				else {
					count_by_id[prot_id] += i;
				}
			}
		}
	}
	std::vector<Sequence> sequences;
	for (auto id_count : count_by_id) {
		if (((float)id_count.second/total_kmers) > threshold) {
			db_index_val_t loc = location_by_idx[id_count.first];
//			DEBUG("id: " << id_count.first << ", pos: " << loc.pos << ", len: " << loc.len);
			string seq(loc.len, '.');
			file_fasta->seekg(loc.pos, file_fasta->beg);
			file_fasta->read(&(seq[0]), loc.len);
			sequences.push_back(parse_sequence(seq));
		}
	}
	return sequences;
}

CbDbReader::~CbDbReader() {
	if (files_opened) {
		file_fasta->close();
		file_kmers->close();
		file_idx->close();
		delete file_fasta;
		delete file_kmers;
		delete file_idx;
	}
}

void CbDbReader::open_files(std::string idb_path) {
	file_fasta = new ifstream(idb_path);
	file_kmers = new fstream(idb_path + string(".cbm"));
	file_idx = new fstream(idb_path + string(".cbi"));
	files_opened = true;
}
