/*
 * options.cpp
 *
 *  Created on: Mar 27, 2026
 *      Author: pjarnot
 */



#include "method/cbsearch-db/options.hpp"
#include "config-cbsearch.h"

#include "debug.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <cstring>
#include <limits>

#include <iostream>

using namespace std;
using namespace cbsearch;

void OptionsCbDb::show_help() {
    cout << "Usage: cbsearch-db [options]\n";
    cout << "\n";
    cout << "Mandatory arguments to long options are mandatory for short options too.\n";
    cout << "\n";
    cout << "Input and output:\n";
    cout << "  -i, --input-db=FILE      Input database path.\n";
    cout << "Miscellaneous:\n";
    cout << "      --help                 Show this help message and exit\n";
    cout << "      --version              Output version information and exit\n";
}


int OptionsCbDb::parse_options(int argc, char **argv)
{
	int retval = 0;

    if (argc < 2) {
		show_help();
		return -1;
    }

	retval = parse_general_options(argc, argv);

    return retval;
}


int OptionsCbDb::parse_general_options(int argc, char **argv) {
    int c;
   while (1)
   {
        int option_index = 0;
        static struct option long_options[] = {
            {"input-db",     required_argument, 0,  'i' },
            {"help",    no_argument,       0,  0 },
            {"version",    no_argument,       0,  0 },
            {0,         0,                 0,  0 }
        };

		c = getopt_long(argc, argv, "i:",
                 long_options, &option_index);

		if (c == -1)
        	break;

		switch (c) {
		case 0:
			if (strcmp(long_options[option_index].name, "help") == 0) {
				show_help();
				return -1;
			}
			else if (strcmp(long_options[option_index].name, "version") == 0) {
				cout << PACKAGE_STRING;
				return -1;
			}
			break;

			case 'i':
            input_db_path = optarg;
            break;

		case '?':
            break;

		default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
	return 0;
}





