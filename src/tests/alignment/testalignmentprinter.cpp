/*
 * testalignmentprinter.cpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */

#include "tests/alignment/testalignmentprinter.hpp"
#include "alignment/alignmentprinter.hpp"

#include "tests/unittest.hpp"

#include <sstream>

using namespace nscsearch;
using namespace std;


void TestAlignmentPrinter::run() {

	initialize_data();

	test_single_line_alignment();
	test_single_full_line_alignment();
	test_one_residue_over_full_line_alignment();
	test_two_and_half_line_alignment();

	std::cerr << "\n";
}


void TestAlignmentPrinter::initialize_data() {
}


void TestAlignmentPrinter::test_single_line_alignment() {
	string expected_result = ""
			"Query     1  MAGQHLP---VPRLEGVSREQFMQHLYPQRKP  29\n"
			"             M  +  P   VP L+GV+RE+F++ +YP+R+P\n"
			"Hit       1  MEQREQPAVQVPSLDGVTRERFLRDVYPRREP  32\n";


	ostringstream oss;
	AlignmentPrinter ap(&oss, 60);
	ap.set_query_alignment("MAGQHLP---VPRLEGVSREQFMQHLYPQRKP");
	ap.set_midline_alignment("M  +  P   VP L+GV+RE+F++ +YP+R+P");
	ap.set_hit_alignment("MEQREQPAVQVPSLDGVTRERFLRDVYPRREP");

	ap.print_alignment();

//	cerr << oss.str() << endl;

	ASSERT(expected_result.compare(oss.str()) == 0);
}


void TestAlignmentPrinter::test_single_full_line_alignment() {
	string expected_result = ""
			"Query     1  MAGQHLP---VPRLEGVSREQFMQHLYPQRKPLVLEGIDLGPCTSKWTVDYLSQVGGKKE  57\n"
			"             M  +  P   VP L+GV+RE+F++ +YP+R+P+VL+G++LGPCT+KWTVDYLSQ  G KE\n"
			"Hit       1  MEQREQPAVQVPSLDGVTRERFLRDVYPRREPVVLKGMELGPCTTKWTVDYLSQAAGSKE  60\n";


	ostringstream oss;
	AlignmentPrinter ap(&oss, 60);
	ap.set_query_alignment("MAGQHLP---VPRLEGVSREQFMQHLYPQRKPLVLEGIDLGPCTSKWTVDYLSQVGGKKE");
	ap.set_midline_alignment("M  +  P   VP L+GV+RE+F++ +YP+R+P+VL+G++LGPCT+KWTVDYLSQ  G KE");
	ap.set_hit_alignment("MEQREQPAVQVPSLDGVTRERFLRDVYPRREPVVLKGMELGPCTTKWTVDYLSQAAGSKE");

	ap.print_alignment();

//	cerr << oss.str() << endl;

	ASSERT(expected_result.compare(oss.str()) == 0);
}


void TestAlignmentPrinter::test_one_residue_over_full_line_alignment() {
	string expected_result = ""
			"Query     1  MAGQHLP---VPRLEGVSREQFMQHLYPQRKPLVLEGIDLGPCTSKWTVDYLSQVGGKKE  57\n"
			"             M  +  P   VP L+GV+RE+F++ +YP+R+P+VL+G++LGPCT+KWTVDYLSQ  G KE\n"
			"Hit       1  MEQREQPAVQVPSLDGVTRERFLRDVYPRREPVVLKGMELGPCTTKWTVDYLSQAAGSKE  60\n"
			"\n"
			"Query    58  V  58\n"
			"             V\n"
			"Hit      61  V  61\n";


	ostringstream oss;
	AlignmentPrinter ap(&oss, 60);
	ap.set_query_alignment("MAGQHLP---VPRLEGVSREQFMQHLYPQRKPLVLEGIDLGPCTSKWTVDYLSQVGGKKEV");
	ap.set_midline_alignment("M  +  P   VP L+GV+RE+F++ +YP+R+P+VL+G++LGPCT+KWTVDYLSQ  G KEV");
	ap.set_hit_alignment("MEQREQPAVQVPSLDGVTRERFLRDVYPRREPVVLKGMELGPCTTKWTVDYLSQAAGSKEV");

	ap.print_alignment();

//	cerr << oss.str() << endl;

	ASSERT(expected_result.compare(oss.str()) == 0);
}


void TestAlignmentPrinter::test_two_and_half_line_alignment() {

	string expected_result = ""
			"Query     1  MAGQHLP---VPRLEGVSREQFMQHLYPQRKPLVLEGIDLGPCTSKWTVDYLSQVGGKKE  57\n"
			"             M  +  P   VP L+GV+RE+F++ +YP+R+P+VL+G++LGPCT+KWTVDYLSQ  G KE\n"
			"Hit       1  MEQREQPAVQVPSLDGVTRERFLRDVYPRREPVVLKGMELGPCTTKWTVDYLSQAAGSKE  60\n"
			"\n"
			"Query    58  VKIHVAAVAQMDFISKNFVYRTLPFDQLVQRAAEEKHKEFFVSEDEKYYLRSLGEDPRKD  117\n"
			"             VKIHV+AV QMDF+SKNFVYRTLPFD  V+RAAE KHK++F+SEDEKYYLRS+GED RKD\n"
			"Hit      61  VKIHVSAVPQMDFLSKNFVYRTLPFDVFVRRAAEVKHKDYFLSEDEKYYLRSVGEDVRKD  120\n"
			"\n"
			"Query   118  VADIRKQFPLLKGDIKFPEFFKEEQ  142\n"
			"             +ADIRKQFP+L  D++ PE+F++EQ\n"
			"Hit     121  IADIRKQFPVLAEDVQIPEYFEKEQ  145\n";


	ostringstream oss;
	AlignmentPrinter ap(&oss, 60);
	ap.set_query_alignment("MAGQHLP---VPRLEGVSREQFMQHLYPQRKPLVLEGIDLGPCTSKWTVDYLSQVGGKKEVKIHVAAVAQMDFISKNFVYRTLPFDQLVQRAAEEKHKEFFVSEDEKYYLRSLGEDPRKDVADIRKQFPLLKGDIKFPEFFKEEQ");
	ap.set_midline_alignment("M  +  P   VP L+GV+RE+F++ +YP+R+P+VL+G++LGPCT+KWTVDYLSQ  G KEVKIHV+AV QMDF+SKNFVYRTLPFD  V+RAAE KHK++F+SEDEKYYLRS+GED RKD+ADIRKQFP+L  D++ PE+F++EQ");
	ap.set_hit_alignment("MEQREQPAVQVPSLDGVTRERFLRDVYPRREPVVLKGMELGPCTTKWTVDYLSQAAGSKEVKIHVSAVPQMDFLSKNFVYRTLPFDVFVRRAAEVKHKDYFLSEDEKYYLRSVGEDVRKDIADIRKQFPVLAEDVQIPEYFEKEQ");

	ap.print_alignment();

//	cerr << oss.str() << endl;

	ASSERT(expected_result.compare(oss.str()) == 0);
}


