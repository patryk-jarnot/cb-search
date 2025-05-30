/*
 * sequencereaderfasta.cpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */



#include "dal/sequencereaderfasta.hpp"

#include "model/sequence.hpp"


namespace nscsearch {

	SequenceReaderFasta::SequenceReaderFasta() {
	}

	SequenceReaderFasta::SequenceReaderFasta(std::istream *istream) {
		open_file(istream);
	}

	SequenceReaderFasta::SequenceReaderFasta(std::string ifile_name) {
		open_file(ifile_name);
	}

	SequenceReaderFasta::~SequenceReaderFasta() {

	}

	void SequenceReaderFasta::open_file(std::istream *istream) {
		fasta_reader.open_file(istream);
	}

	void SequenceReaderFasta::open_file(std::string ipath) {
		fasta_reader.open_file(ipath);
	}

	bool SequenceReaderFasta::has_next_sequence() {
		return fasta_reader.has_next_sequence();
	}

	Sequence SequenceReaderFasta::get_next_sequence() {
		fasta::Sequence *fasta_seq = fasta_reader.read_next_sequence();

		return Sequence(fasta_seq->header, fasta_seq->sequence);
	}
}

