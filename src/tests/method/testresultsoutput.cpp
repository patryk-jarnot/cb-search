/*
 * testresultsoutput.cpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */


#include "tests/method/testresultsoutput.hpp"
#include "utils/fileutils.hpp"
#include "model/results.hpp"
#include "tests/unittest.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "method/resultsoutput.hpp"

using namespace nscsearch;
using namespace std;


void test_single_hit_json() {
	string expected = ""
			"{\n"
			"	\"query_header\": \">query header\",\n"
			"	\"hits\": [\n"
			"		{\n"
			"			\"query_alignment\": \"ASDF\",\n"
			"			\"midline\": \" +DF\",\n"
			"			\"hit_alignment\": \"QWDF\",\n"
			"			\"hit_header\": \">hit header\",\n"
			"			\"score\": 20,\n"
			"			\"simi_score\": 0.8,\n"
			"			\"similarity\": 0.75,\n"
			"			\"identity\": 0.5\n"
			"		}\n"
			"	]\n"
			"}\n";
	stringstream observed_stream;
	ResultsOutput ro;
//	ro.process_record();
	results_t results;
	results.query_header = ">query header";

	results_item_t item;
	item.query_alignment = "ASDF";
	item.midline_alignment = " +DF";
	item.hit_alignment = "QWDF";
	item.hit_header = ">hit header";
	item.score = 20;
	item.simi_score = 0.8;
	item.similarity = 0.75;
	item.identity = 0.5;

	results.alignments.push_back(item);
	ro.print_records(&observed_stream, &results, 100, OutputFormat::JSON);
	string observed = observed_stream.str();

//	cerr << observed << "\n\n";
//	cerr << expected << "\n\n";

	ASSERT(expected.compare(observed) == 0);
}


void test_two_hits_json() {
	string expected = ""
			"{\n"
			"	\"query_header\": \">query header\",\n"
			"	\"hits\": [\n"
			"		{\n"
			"			\"query_alignment\": \"ASDF\",\n"
			"			\"midline\": \" +DF\",\n"
			"			\"hit_alignment\": \"QWDF\",\n"
			"			\"hit_header\": \">hit header\",\n"
			"			\"score\": 20,\n"
			"			\"simi_score\": 0.8,\n"
			"			\"similarity\": 0.75,\n"
			"			\"identity\": 0.5\n"
			"		},\n"
			"		{\n"
			"			\"query_alignment\": \"ASDF\",\n"
			"			\"midline\": \" +DF\",\n"
			"			\"hit_alignment\": \"VWDF\",\n"
			"			\"hit_header\": \">hit header2\",\n"
			"			\"score\": 18,\n"
			"			\"simi_score\": 0.8,\n"
			"			\"similarity\": 0.75,\n"
			"			\"identity\": 0.5\n"
			"		}\n"
			"	]\n"
			"}\n";
	stringstream observed_stream;
	ResultsOutput ro;
//	ro.process_record();
	results_t results;
	results.query_header = ">query header";

	results_item_t item;
	item.query_alignment = "ASDF";
	item.midline_alignment = " +DF";
	item.hit_alignment = "QWDF";
	item.hit_header = ">hit header";
	item.score = 20;
	item.similarity = 0.75;
	item.simi_score = 0.80;
	item.identity = 0.5;
	results.alignments.push_back(item);

	item.query_alignment = "ASDF";
	item.midline_alignment = " +DF";
	item.hit_alignment = "VWDF";
	item.hit_header = ">hit header2";
	item.score = 18;
	item.similarity = 0.75;
	item.simi_score = 0.80;
	item.identity = 0.5;
	results.alignments.push_back(item);

	ro.print_records(&observed_stream, &results, 100, OutputFormat::JSON);
	string observed = observed_stream.str();

	ASSERT(expected.compare(observed) == 0);
}


void TestResultsOutput::run() {

	initialize_data();
	test_single_hit();
	test_two_hits();

	test_two_hits_sort_by_score();
	test_two_hits_sort_by_identity();
	test_two_hits_sort_by_similarity();

	test_two_hits_filter_by_score();
	test_two_hits_filter_by_identity();
	test_two_hits_filter_by_similarity();

	test_two_hits_limit_to_one();
	test_two_hits_limit_to_two();

	test_single_hit_json();
	test_two_hits_json();

	std::cerr << "\n";
}


void TestResultsOutput::initialize_data() {

}


void TestResultsOutput::test_single_hit() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header                                                     20     0.8000    0.5000      0.7500\n"
			"\n"
			"\n"
			">hit header\n"
			"Score: 20    SimiScore: 0.8    Identity: 0.5    Similarity: 0.75\n"
			"\n"
			"Query     1  ASDF  4\n"
			"              +DF\n"
			"Hit       1  QWDF  4\n"
			"\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro;
//	ro.process_record();
	results_t results;
	results_item_t item;
	item.query_alignment = "ASDF";
	item.midline_alignment = " +DF";
	item.hit_alignment = "QWDF";
	item.hit_header = ">hit header";
	item.score = 20;
	item.identity = 0.5;
	item.similarity = 0.75;
	item.simi_score = 0.8;

	results.alignments.push_back(item);
	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed) == 0);
}


void TestResultsOutput::test_two_hits() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 2                                                   30     0.8000    0.6667      0.8333\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			"\n"
			"\n"
			">hit header 2\n"
			"Score: 30    SimiScore: 0.8    Identity: 0.6667    Similarity: 0.8333\n"
			"\n"
			"Query     1  QWERTY  6\n"
			"             QW+ TY\n"
			"Hit       1  QWD-TY  5\n"
			"\n"
			"\n"
			">hit header 1\n"
			"Score: 20    SimiScore: 0.8    Identity: 0.5    Similarity: 0.75\n"
			"\n"
			"Query     1  ASDF  4\n"
			"              +DF\n"
			"Hit       1  QWDF  4\n"
			"\n"
			"\n";
	stringstream observed_stream;

	results_t results;
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 30, 0.8, 0.6667, 0.8333));
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));

	ResultsOutput ro;
	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed) == 0);
}


void TestResultsOutput::test_two_hits_sort_by_score() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 2                                                   30     0.8000    0.6667      0.8333\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro;
	results_t results;
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 30, 0.8, 0.6667, 0.8333));

	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}


void TestResultsOutput::test_two_hits_sort_by_identity() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 2                                                   10     0.8000    0.8667      0.5333\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro(SortOutputBy::IDENTITY);

	results_t results;
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 10, 0.8, 0.8667, 0.5333));

	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}


void TestResultsOutput::test_two_hits_sort_by_similarity() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 2                                                   10     0.8000    0.4667      0.8333\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro(SortOutputBy::SIMILARITY);

	results_t results;
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 10, 0.8, 0.4667, 0.8333));

	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}


void TestResultsOutput::test_two_hits_filter_by_score() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro(SortOutputBy::SCORE, 12);

	results_t results;
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 10, 0.8, 0.4667, 0.8333));

	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}


void TestResultsOutput::test_two_hits_filter_by_identity() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro(SortOutputBy::IDENTITY, 0.48);

	results_t results;
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 10, 0.8, 0.4667, 0.8333));

	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}


void TestResultsOutput::test_two_hits_filter_by_similarity() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 2                                                   10     0.8000    0.4667      0.8333\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro(SortOutputBy::SIMILARITY, 0.8);

	results_t results;
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 10, 0.8, 0.4667, 0.8333));

	ro.print_records(&observed_stream, &results);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}


void TestResultsOutput::test_two_hits_limit_to_one() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro;

	results_t results;
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 10, 0.8, 0.4667, 0.8333));

	ro.print_records(&observed_stream, &results, 1);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}


void TestResultsOutput::test_two_hits_limit_to_two() {
	string expected = ""
			"Header                                                       Score  SimiScore  Identity  Similarity\n"
			">hit header 1                                                   20     0.8000    0.5000      0.7500\n"
			">hit header 2                                                   10     0.8000    0.4667      0.8333\n"
			"\n";
	stringstream observed_stream;
	ResultsOutput ro;

	results_t results;
	results.alignments.push_back(results_item_t("QWERTY", "QW+ TY", "QWD-TY", ">hit header 2", 10, 0.8, 0.4667, 0.8333));
	results.alignments.push_back(results_item_t("ASDF", " +DF", "QWDF", ">hit header 1", 20, 0.8, 0.5, 0.75));

	ro.print_records(&observed_stream, &results, 2);
	string observed = observed_stream.str();

//	istringstream expected_stream(expected);
//	observed_stream.seekg(0);
//	string expected_line;
//	string observed_line;
//	while (getline(expected_stream, expected_line) && getline(observed_stream, observed_line)) {
//		cerr << "expected line: " << expected_line << endl;
//		cerr << "observed line: " << observed_line << endl;
//		ASSERT(expected_line.compare(observed_line) == 0);
//	}

	ASSERT(expected.compare(observed.substr(0, expected.length())) == 0);
}

