/*
 * fasta.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#include "utils/fasta.hpp"

#include <fstream>
#include <vector>
#include <map>
#include <cstring>

using namespace fasta;
using namespace std;


Sequence FastaReader::read_sequence()
{
	Sequence retval;
	std::getline(*input_stream, retval.header);
	if (retval.header.length() == 0 || retval.header[0] != '>')
	{
		throw "invalid header";
	}

	while ((!input_stream->eof() && input_stream->peek() != EOF) && input_stream->peek() != '>')
	{
		std::string tmp;
		std::getline(*input_stream, tmp);

		retval.sequence += tmp;
	}

//	cout.flush();
	return retval;
}

Sequence* FastaReader::read_sequence_ptr()
{
	Sequence *retval = new Sequence();
	std::getline(*input_stream, retval->header);
	if (retval->header.length() == 0 || retval->header[0] != '>')
	{
		throw "invalid header";
	}

	while ((!input_stream->eof() && input_stream->peek() != EOF) && input_stream->peek() != '>')
	{
		std::string tmp;
		std::getline(*input_stream, tmp);

		retval->sequence += tmp;
	}

//	cout.flush();
	return retval;
}


FastaReader::FastaReader() : initialized_stream(false), input_stream(nullptr)
{
}

FastaReader::FastaReader(istream *istream) : initialized_stream(false)
{
	input_stream = istream;
}


FastaReader::FastaReader(std::string ifileName) : initialized_stream(true)
{
	open_file(ifileName);
}


void FastaReader::open_file(std::istream *istream) {
	input_stream = istream;
}


void FastaReader::open_file(std::string ifile_name) {
	input_stream = new ifstream(ifile_name);
}


FastaReader::~FastaReader() {
	if (initialized_stream)
	{
		((ifstream*)input_stream)->close();
		delete input_stream;
	}
}


bool FastaReader::has_next_sequence() {
	return !input_stream->eof() && input_stream->peek() != EOF;
}


Sequence* FastaReader::read_next_sequence() {
	if (!input_stream->eof() && input_stream->peek() != EOF)
	{
		//current.reset(readSequencePtr());
		current = std::unique_ptr<Sequence>(read_sequence_ptr());
	}

	return current.get();
}


std::vector<Sequence> FastaReader::read_sequences()
{
	std::vector<Sequence> retval;

	while (!input_stream->eof() && input_stream->peek() != EOF)
	{
		Sequence s = read_sequence();
		retval.push_back(s);
	}

	return retval;
}


string FastaReader::read_acc(string header) {
	size_t beg = header.find('|', 0) + 1;
	size_t end = header.find('|', beg) - 1;
	return header.substr(beg, end - beg + 1);
}


std::map<string, Sequence> FastaReader::read_sequences_by_id()
{
	std::map<string, Sequence> retval;

	while (!input_stream->eof() && input_stream->peek() != EOF)
	{
		Sequence s = read_sequence();
		string protein_acc = read_acc(s.header);
		retval[protein_acc] = s;
	}

	return retval;
}


void FastaWriter::write_sequence(Sequence isequence)
{
	output_stream->write(isequence.header.c_str(), isequence.header.length());
	output_stream->write("\n", 1);
	output_stream->write(isequence.sequence.c_str(), isequence.sequence.length());
	output_stream->write("\n", 1);
}


FastaWriter::FastaWriter(std::ostream *istream) : initialized_stream(false)
{
	output_stream = istream;
}


FastaWriter::FastaWriter(std::string ifileName) : initialized_stream(true)
{
	output_stream = new ofstream(ifileName);
}


FastaWriter::~FastaWriter()
{
	if (initialized_stream)
	{
		((ofstream*)output_stream)->close();
		delete output_stream;
	}
}


void FastaWriter::write_sequences(std::vector<Sequence> isequences)
{
	for (auto s : isequences)
	{
		write_sequence(s);
	}
}


FastaClusterReader::FastaClusterReader(std::string ipath) {
	dir = opendir(ipath.c_str());
	cluster_path = ipath;
}

bool FastaClusterReader::has_next_cluster() {
	if (!next) {
		dirent *ent;
		ent = readdir(dir);
		while (ent) {
			if (strcmp((const char *)ent->d_name, ".") == 0 || strcmp((const char *)ent->d_name, "..") == 0) {
				ent = readdir(dir);
				continue;
			}

			Cluster *clst = new Cluster();
			clst->model = ent->d_name;
			clst->model = clst->model.substr(0, clst->model.size()-6);
			clst->path += cluster_path;
			clst->path += "/";
			clst->path += ent->d_name;
			FastaReader fr(clst->path);
			clst->sequences = fr.read_sequences();
			next = std::unique_ptr<Cluster>(clst);
			return true;
		}
		return false;
	}
	else {
		return true;
	}
}

Cluster *FastaClusterReader::read_next_cluster() {
	if (has_next_cluster()) {
		current = move(next);
		return current.get();
	}
	else {
		return nullptr;
	}
}

