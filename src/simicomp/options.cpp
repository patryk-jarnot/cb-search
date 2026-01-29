/*
 * options.cpp
 *
 *  Created on: Jan 29, 2026
 *      Author: pjarnot
 */


#include "simicomp/options.hpp"
#include "config-cbsearch.h"

#include "debug.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <cstring>
#include <limits>

#include <iostream>

using namespace std;
using namespace nscsearch;

void OptionsSc::show_help() {
    cout << "Usage: simicomp [options]\n";
    cout << "\n";
    cout << "Mandatory arguments to long options are mandatory for short options too.\n";
    cout << "\n";
    cout << "Input and output:\n";
    cout << "  -q, --query-file=FILE      Path to query file in fasta format. If not specified,\n";
    cout << "                               stdin will be used\n";
    cout << "  -d, --database-file=FILE   Path to database file in fasta format.\n";
    cout << "  -o, --output-file=FILE     Path to file storing output. If not specified, stdout\n";
    cout << "                               will be used\n";
    cout << "\n";
    cout << "SimiComp:\n";
    cout << "      --threads=INT          Determines how many threads will be used (default: " << thread_count << ")\n";
    cout << "  -l, --limit=INT            Maximal number of results reported by the method.\n";
    cout << "                               Negative value turns off filtering (default: " << limit << ")\n";
    cout << "  -s  --similarity-thr=FLOAT When scanning sequences select only motifs with higher\n";
    cout << "                               composition similarity (default: " << similarity_threshold << ")\n";
    cout << "  -r  --relative-thr=FLOAT   When resizing motifs keep this value as minimum similarity\n";
    cout << "                               as relative initially identified motif (default: " << relative_threshold << ")\n";
    cout << "\n";
    cout << "Miscellaneous:\n";
    cout << "      --help                 Show this help message and exit\n";
    cout << "      --version              Output version information and exit\n";
    cout << "      --debug=LEVEL          Set debug level (default: " << debug_level <<"\n";
}


int OptionsSc::parse_options(int argc, char **argv)
{
	int retval = 0;

    if (argc < 2) {
		show_help();
		return -1;
    }

	retval = parse_general_options(argc, argv);

    return retval;
}


int OptionsSc::parse_general_options(int argc, char **argv) {
    int c;
   while (1)
   {
        int option_index = 0;
        static struct option long_options[] = {
            {"query-file",     required_argument, 0,  'q' },
            {"database-file",     required_argument, 0,  'd' },
            {"output-file",     required_argument, 0,  'o' },
            {"threads",     required_argument, 0,  0 },
            {"similarity-thr",     required_argument, 0,  's' },
            {"relative-thr",     required_argument, 0,  'r' },
            {"limit",     required_argument, 0,  'l' },
            {"help",    no_argument,       0,  0 },
            {"version",    no_argument,       0,  0 },
            {"debug",    required_argument,       0,  0 },
            {0,         0,                 0,  0 }
        };

		c = getopt_long(argc, argv, "q:d:o:s:r:l:",
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
        	else if (strcmp(long_options[option_index].name, "debug") == 0) {
        		debug_level = atoi(optarg);
        	}
        	else if (strcmp(long_options[option_index].name, "threads") == 0) {
				thread_count = atoi(optarg);
				if (thread_count < 2) {
					thread_count = 1;
				}
        	}
            break;

       case 'q':
            query_file_path = optarg;
            break;

       case 'd':
            database_file_path = optarg;
            break;

       case 'o':
            output_file_path = optarg;
            break;

       case 'l':
            limit = atoi(optarg);
            if (limit < 0) {
            	limit = std::numeric_limits<int>::max();
            }
            break;

       case 's':
            similarity_threshold = atof(optarg);
            break;

       case 'r':
            relative_threshold = atof(optarg);
            break;

       case '?':
            break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
	return 0;
}




