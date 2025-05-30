/*
 * fileutils.cpp
 *
 *  Created on: Apr 8, 2023
 *      Author: pjarnot
 */

#include "utils/fileutils.hpp"
#include "exceptions.hpp"

#include <sstream>
#include <fstream>

using namespace std;


namespace nscsearch {

	string read_file(string const& ifile_path) {
		ifstream t(ifile_path);
		if (t.fail()) {
			throw_file_not_found(ifile_path);
		}

		stringstream buffer;
		buffer << t.rdbuf();
		return buffer.str();
	}

}


