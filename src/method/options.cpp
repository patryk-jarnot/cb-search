/*
 * options.cpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */


#include "method/options.hpp"
#include "config-nscsearch.h"

#include "debug.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <cstring>
#include <limits>

#include <iostream>

using namespace std;
using namespace nscsearch;

void Options::show_help() {
    cout << "Usage: nscsearch [options]\n";
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
    cout << "Algorithm:\n";
    cout << "      --threads=INT          Determines how many threads will be used (default: " << thread_count << ")\n";
    cout << "  -a, --align=INT            Specifies alignment algorithm\n";
    cout << "                               0 - Global\n";
    cout << "                               1 - Global-to-local (default)\n";
    cout << "                               2 - Local\n";
    cout << "  -s, --sort=INT             Determines which column will be used to sort output\n";
    cout << "                               0 - None\n";
    cout << "                               1 - Score\n";
    cout << "                               2 - SimiScore (default)\n";
    cout << "                               3 - Identity\n";
    cout << "                               4 - Similarity\n";
    cout << "  -f, --output-format=INT    Specifies format in which results will be presented\n";
    cout << "                               0 - Human readable (default)\n";
    cout << "                               1 - JSON\n";
    cout << "  -t, --threshold=FLOAT      Determines minimal value of sorted column in output\n";
    cout << "                               records. (default: " << threshold << ")\n";
    cout << "  -l, --limit=INT            Maximal number of results reported by the method.\n";
    cout << "                               Negative value turns off filtering (default: " << limit << ")\n";
    cout << "      --umask-residues=STR   Specify residues for calculation according to scoring\n";
    cout << "                               matrix. Rest will be masked(default: turned off)\n";
    cout << "      --cbr-corr-alpha=FLOAT Set alpha value for CBR correction.\n";
    cout << "                               (default: " << alpha_of_cbr_correction << ")\n";
    cout << "      --gap-open=FLOAT       Gap open cost. (default: " << gap_open << ")\n";
    cout << "      --gap-extend=FLOAT     Gap extension cost. (default: " << gap_extension << ")\n";
    cout << "\n";
    cout << "SimiComp:\n";
    cout << "      --simi-comp            If set, the method will search for compositionally\n";
    cout << "                               similar fragments to the query in the database.\n";
    cout << "                               (default: " << is_composition_identification << ")\n";
    cout << "      --similarity-thr=FLOAT When scanning sequences select only motifs with higher\n";
    cout << "                               composition similarity (default: " << similarity_threshold << ")\n";
    cout << "      --relative-thr=FLOAT   When resizing motifs keep this value as minimum similarity\n";
    cout << "                               as relative initially identified motif (default: " << relative_threshold << ")\n";
    cout << "\n";
    cout << "Miscellaneous:\n";
    cout << "      --help                 Show this help message and exit\n";
    cout << "      --version              Output version information and exit\n";
    cout << "      --debug=LEVEL          Set debug level (default: " << debug_level <<"\n";
}


int Options::parse_options(int argc, char **argv)
{
	int retval = 0;

    if (argc < 2) {
		show_help();
		return -1;
    }

	retval = parse_general_options(argc, argv);

    return retval;
}


int Options::parse_general_options(int argc, char **argv) {
    int c;
   while (1)
   {
        int option_index = 0;
        static struct option long_options[] = {
            {"query-file",     required_argument, 0,  'q' },
            {"database-file",     required_argument, 0,  'd' },
            {"output-file",     required_argument, 0,  'o' },
            {"threshold",     required_argument, 0,  't' },
            {"sort",     required_argument, 0,  's' },
            {"align",     required_argument, 0,  'a' },
            {"output-format",     required_argument, 0,  'f' },
            {"threads",     required_argument, 0,  0 },
            {"gap-open",     required_argument, 0,  0 },
            {"gap-extend",     required_argument, 0,  0 },
            {"simi-comp",     no_argument, 0,  0 },
            {"similarity-thr",     required_argument, 0,  0 },
            {"relative-thr",     required_argument, 0,  0 },
            {"help",    no_argument,       0,  0 },
            {"version",    no_argument,       0,  0 },
            {"debug",    required_argument,       0,  0 },
            {"umask-residues",    required_argument,       0,  0 },
            {"cbr-corr-alpha",    required_argument,       0,  0 },
            {0,         0,                 0,  0 }
        };

		c = getopt_long(argc, argv, "q:d:o:t:s:a:l:f:",
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
        	else if (strcmp(long_options[option_index].name, "gap-open") == 0) {
        		gap_open = atof(optarg);
        	}
        	else if (strcmp(long_options[option_index].name, "gap-extend") == 0) {
        		gap_extension = atof(optarg);
        	}
        	else if (strcmp(long_options[option_index].name, "simi-comp") == 0) {
        		is_composition_identification = true;
        	}
        	else if (strcmp(long_options[option_index].name, "similarity-thr") == 0) {
        		similarity_threshold = atof(optarg);
        	}
        	else if (strcmp(long_options[option_index].name, "relative-thr") == 0) {
        		relative_threshold = atof(optarg);
        	}
        	else if (strcmp(long_options[option_index].name, "threads") == 0) {
				thread_count = atoi(optarg);
				if (thread_count < 2) {
					thread_count = 1;
				}
        	}
        	else if (strcmp(long_options[option_index].name, "umask-residues") == 0) {
				unmasked_residues = string(optarg);
        	}
        	else if (strcmp(long_options[option_index].name, "cbr-corr-alpha") == 0) {
				alpha_of_cbr_correction = atof(optarg);
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

       case 't':
            threshold = atof(optarg);
            break;

       case 'l':
            limit = atoi(optarg);
            if (limit < 0) {
            	limit = std::numeric_limits<int>::max();
            }
            break;

       case 's':
            sort_output_by = static_cast<SortOutputBy>(atoi(optarg));
            break;

       case 'a':
            align_algorithm = static_cast<AlignAlgorithm>(atoi(optarg));
            break;

       case 'f':
            output_format = static_cast<OutputFormat>(atoi(optarg));
            break;

       case '?':
            break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
	return 0;
}

