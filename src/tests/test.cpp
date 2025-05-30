/*
 * test.cpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#include "tests/alignment/nw/testnwgapaffinitymatrices.hpp"
#include "tests/alignment/nw/testneedlemanwunsch.hpp"
#include "tests/alignment/og/testoggapaffinitymatrices.hpp"
#include "tests/alignment/og/testonewayglobal.hpp"
#include "tests/alignment/testalignmentprinter.hpp"
#include "tests/identification/testfragmentextender.hpp"
#include "tests/method/testnscsearch.hpp"
#include "tests/method/testresultsoutput.hpp"
#include "tests/method/testoptions.hpp"
#include "tests/filters/testshortword.hpp"
#include "tests/dal/testsequencereaderfasta.hpp"
#include "tests/utils/teststringutils.hpp"
#include "tests/utils/testfileutils.hpp"
#include "tests/utils/testnumericutils.hpp"
#include "tests/utils/testfunctionutils.hpp"

#include "tests/unittest.hpp"

#include "debug.hpp"

#include <iostream>
#include <limits>
#include "tests/identification/testcompositioncalculator.hpp"
#include "tests/identification/testcompositionmatrix.hpp"
#include "tests/identification/testcompositionsimilarity.hpp"
#include "tests/identification/testsequencefrequency.hpp"
#include "tests/identification/testsimicomp.hpp"
#include "tests/residue/testmatrixrecalculator.hpp"
#include "tests/residue/testscoringmatrix.hpp"
#include "tests/residue/testalphabetreduction.hpp"

using namespace std;
using namespace nscsearch;


int main(int argc, char **argv) {
	string root_path = string(argv[1]);

//	subscribe_stacktrace(std::numeric_limits<int>::max());

    cerr << "----- STARTED TESTS -----\n\n";

    TestStringUtils tsu;
    tsu.run();

    TestNumericUtils tnu;
    tnu.run();

    TestFileUtils test_file_utils;
    test_file_utils.run(root_path);

    TestFunctionUtils test_function_utils;
    test_function_utils.run();

    TestOptions to;
    to.run();

    TestSequenceReaderFasta tsrf;
    tsrf.run(root_path);

    TestNwGapAffinityMatrices tngam;
    tngam.run();

    TestOgGapAffinityMatrices togam;
    togam.run();

    TestAlphabetReduction tar;
    tar.run();

    TestMatrixRecalculator tmr;
    tmr.run();

    TestScoringMatrix tsm;
    tsm.run();

    TestNeedlemanWunsch tnw;
    tnw.run();

    TestOneWayGlobal towg;
    towg.run();

    TestCompositionMatrix tcm;
    tcm.run();

    TestCompositionCalculator tcc;
    tcc.run();

    TestCompositionSimilarity tcs;
    tcs.run();

    TestFragmentExtender tfe;
    tfe.run();

    TestNscSearch tns;
    tns.run();

    TestResultsOutput tro;
    tro.run();

    TestAlignmentPrinter tap;
    tap.run();

    TestSequenceFrequency tsf;
    tsf.run();

    TestSimiComp tsc;
    tsc.run();

    TestShortWordFilter tswf;
    tswf.run();

    cerr << "----- FINISHED TESTS -----\n";
	std::cerr << "\033[32m" << UNIT_TESTS_PASSED_COUNTER << " asserts passed\033[39;49m, and \033[31m" << UNIT_TESTS_FAILED_COUNTER << " asserts failed\033[39;49m.\n\n";

    return 0;
}

