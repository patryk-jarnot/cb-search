/*
 * fasta.h
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_FASTA_H_
#define GBSC_INCLUDE_FASTA_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <memory>

#include "dirent.h"


namespace fasta
{
	struct Sequence {
		Sequence() { }
		Sequence(std::string iheader, std::string isequence) : header(iheader), sequence(isequence) { }

		std::string header;
		std::string sequence;
	};


	struct Cluster {
		Cluster() {}
		Cluster(std::string imodel, std::string ipath, std::vector<Sequence> isequences) : model(imodel), path(ipath), sequences(isequences) { }

		std::string model;
		std::string path;
		std::vector<Sequence> sequences;
	};


	class FastaReader
	{
	private:
		bool initialized_stream;
		std::istream *input_stream;

		std::unique_ptr<Sequence> current;

		Sequence read_sequence();
		Sequence* read_sequence_ptr();
		std::string read_acc(std::string header);
	protected:
	public:
		FastaReader();
		FastaReader(std::istream *istream);
		FastaReader(std::string ifile_name);
		virtual ~FastaReader();

		void open_file(std::istream *istream);
		void open_file(std::string ifile_name);

		std::vector<Sequence> read_sequences();
		std::map<std::string, Sequence> read_sequences_by_id();

		bool has_next_sequence();
		Sequence* read_next_sequence();
	};


	class FastaWriter
	{
	private:
		bool initialized_stream;
		std::ostream *output_stream;

		void write_sequence(Sequence isequence);
	protected:
	public:
		FastaWriter(std::ostream *istream);
		FastaWriter(std::string ifile_name);
		virtual ~FastaWriter();

		void write_sequences(std::vector<Sequence> isequences);
	};


	class FastaClusterReader {
	public:
		FastaClusterReader(std::string ipath);

		bool has_next_cluster();
		Cluster *read_next_cluster();

	private:
		DIR *dir;
		std::string cluster_path;
		std::unique_ptr<Cluster> current;
		std::unique_ptr<Cluster> next;

	};
}


#endif /* GBSC_INCLUDE_FASTA_H_ */
