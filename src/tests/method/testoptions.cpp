/*
 * testoptions.cpp
 *
 *  Created on: May 20, 2023
 *      Author: pjarnot
 */


#include "tests/method/testoptions.hpp"

#include "tests/unittest.hpp"

#include <getopt.h>

#include "debug.hpp"

#include <iostream>
#include <sstream>

using namespace nscsearch;
using namespace std;


void test_set_fragment_identification() {
	Options opt;
	int argc = 4;
	char* argv[64] = {(char*)"./testnscsearch", (char*)"--simi-comp", (char*)"-d", (char*)"x"};

	optind = 1;
	opt.parse_options(argc, argv);

	ASSERT(opt.get_is_composition_identification());
}


void test_set_output_format_default() {
	Options opt;
	int argc = 3;
	char* argv[64] = {(char*)"./nscsearch", (char*)"-d", (char*)"x"};

	optind = 1;
	opt.parse_options(argc, argv);


	ASSERT(opt.get_output_format() == OutputFormat::HUMAN);
}


void test_set_output_format_json() {
	Options opt;
	int argc = 5;
	char* argv[64] = {(char*)"./testnscsearch", (char*)"--output-format", (char*)"1", (char*)"-d", (char*)"x"};

	optind = 1;
	opt.parse_options(argc, argv);

	ASSERT(opt.get_output_format() == OutputFormat::JSON);
}


void TestOptions::run() {
	test_set_fragment_identification();
	test_set_output_format_default();
	test_set_output_format_json();

	std::cerr << "\n";
}






