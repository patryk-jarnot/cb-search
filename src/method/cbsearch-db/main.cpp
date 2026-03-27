/*
 * main.cpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */

#include "method/cbsearch-db/options.hpp"
#include "dal/cbdb/cbdbwriter.hpp"

#include <iostream>


using namespace std;
using namespace cbsearch;


class FileInitializer {
public:
	FileInitializer() {}
	virtual ~FileInitializer() {}
	ifstream* open_input(string input_path) {
		input.open(input_path);
		return &input;
	}

	fstream* open_output_mers(string input_path) {
		output_mers.open(input_path + string(".cbm"), ios::in | ios::out | ios::trunc | ios::binary);
		return &output_mers;
	}

	fstream* open_output_idx(string input_path) {
		output_idx.open(input_path + string(".cbi"), ios::in | ios::out | ios::trunc | ios::binary);
		return &output_idx;
	}

private:
	ifstream input;
	fstream output_mers;
	fstream output_idx;
};


int main(int argc, char **argv) {
	try {
		OptionsCbDb opt;

		int status = opt.parse_options(argc, argv);
		if (status < 0)
			return status;

		FileInitializer fi;

		ifstream *input = fi.open_input(opt.get_input_db_path());
		fstream *output_mers = fi.open_output_mers(opt.get_input_db_path());
		fstream *output_idx = fi.open_output_idx(opt.get_input_db_path());

		CbDbWriter writer;
		writer.set_handlers(input, output_mers, output_idx);
		writer.initialize_file();
		writer.fill_the_file();
	}
	catch (std::logic_error &e) {
		cerr << e.what();
		return -1;
	}

    return 0;
}

