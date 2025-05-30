/*
 * sequencereaderfasta.hpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_DAL_SEQUENCEREADERFASTA_HPP_
#define NSCSEARCH_INCLUDE_DAL_SEQUENCEREADERFASTA_HPP_


#include "dal/sequencereader.hpp"

#include "model/sequence.hpp"
#include "utils/fasta.hpp"


namespace nscsearch {

	class SequenceReaderFasta : public SequenceReader {
	public:
		SequenceReaderFasta();
		SequenceReaderFasta(std::istream *istream);
		SequenceReaderFasta(std::string ifile_name);
		virtual ~SequenceReaderFasta();
		virtual bool has_next_sequence();
		virtual Sequence get_next_sequence();
		virtual void open_file(std::string ipath);
		virtual void open_file(std::istream *istream);

	private:
		fasta::FastaReader fasta_reader;

	};

}



#endif /* NSCSEARCH_INCLUDE_DAL_SEQUENCEREADERFASTA_HPP_ */
