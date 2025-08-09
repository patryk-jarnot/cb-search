#AM_CXXFLAGS = -pedantic -Wall -std=c++11 -Iinclude -I$(top_srcdir)/include -DNDEBUG -O2 -pthread
#AM_CXXFLAGS = -g -rdynamic -pedantic -Wall -std=c++11 -I$(top_srcdir)/include -pthread
AM_CXXFLAGS = -g -fpic -Wall -std=c++11 -I$(top_srcdir)/include -pthread
AM_LDFLAGS =

ACLOCAL_AMFLAGS = -I m4 --install
all: libcbsearch.la cbsearch $(builddir)/cbsearch.py test

bin_PROGRAMS = cbsearch testcbsearch


lib_LTLIBRARIES = libcbsearch.la
libcbsearch_la_SOURCES = include/method/nscsearch.hpp src/method/nscsearch.cpp \
		include/constants.hpp \
		include/exceptions.hpp \
		include/python/examples.hpp src/python/examples.cpp \
		include/python/cbsearch.hpp src/python/cbsearch.cpp \
		include/python/identification.hpp src/python/identification.cpp \
		include/method/options.hpp src/method/options.cpp \
		include/method/resultsoutput.hpp src/method/resultsoutput.cpp \
		include/debug.hpp src/debug.cpp \
		include/model/resultsitem.hpp \
		include/model/results.hpp \
		include/model/sequence.hpp src/model/sequence.cpp \
		include/model/fragment.hpp src/model/fragment.cpp \
		include/model/matrixresidue.hpp src/model/matrixresidue.cpp \
		include/dal/sequencereader.hpp src/dal/sequencereader.cpp \
		include/dal/sequencereaderfasta.hpp src/dal/sequencereaderfasta.cpp \
		include/dal/sequencereaderstub.hpp src/dal/sequencereaderstub.cpp \
		include/utils/threadpool.hpp src/utils/threadpool.cpp \
		include/utils/fasta.hpp src/utils/fasta.cpp \
		include/utils/stringutils.hpp src/utils/stringutils.cpp \
		include/utils/fileutils.hpp src/utils/fileutils.cpp \
		include/utils/functionutils.hpp src/utils/functionutils.cpp \
		include/utils/numericutils.hpp src/utils/numericutils.cpp \
		include/residue/scoringmatrix.hpp src/residue/scoringmatrix.cpp \
		include/residue/matrixrecalculator.hpp src/residue/matrixrecalculator.cpp \
		include/residue/alphabetreduction.hpp src/residue/alphabetreduction.cpp \
		include/identification/compositioncalculator.hpp src/identification/compositioncalculator.cpp \
		include/identification/compositionmatrix.hpp src/identification/compositionmatrix.cpp \
		include/identification/compositionsimilarity.hpp src/identification/compositionsimilarity.cpp \
		include/identification/simicomp.hpp src/identification/simicomp.cpp \
		include/identification/frequencyidentificator.hpp src/identification/frequencyidentificator.cpp \
		include/identification/fragmentextender.hpp src/identification/fragmentextender.cpp \
		include/identification/sequencefrequency.hpp src/identification/sequencefrequency.cpp \
		include/filters/kmer.hpp src/filters/kmer.cpp \
		include/filters/composition.hpp src/filters/composition.cpp \
		include/filters/shortword.hpp src/filters/shortword.cpp \
		include/filters/filterpipeline.hpp src/filters/filterpipeline.cpp \
		include/filters/filterbase.hpp \
		include/alignment/alignmentprinter.hpp src/alignment/alignmentprinter.cpp \
		include/alignment/alignbase.hpp src/alignment/alignbase.cpp \
		include/alignment/sw/swgapaffinitymatrices.hpp src/alignment/sw/swgapaffinitymatrices.cpp \
		include/alignment/sw/smithwaterman.hpp src/alignment/sw/smithwaterman.cpp \
		include/alignment/og/oggapaffinitymatrices.hpp src/alignment/og/oggapaffinitymatrices.cpp \
		include/alignment/og/onewayglobal.hpp src/alignment/og/onewayglobal.cpp \
		include/alignment/nw/nwgapaffinitymatrices.hpp src/alignment/nw/nwgapaffinitymatrices.cpp \
		include/alignment/nw/needlemanwunsch.hpp src/alignment/nw/needlemanwunsch.cpp

	

# [begin] BUILD PYTHON PACKAGE
	
BUILT_SOURCES = $(builddir)/cbsearch.py $(builddir)/cbsearch_wrap.cpp

$(builddir)/cbsearch.py $(builddir)/cbsearch_wrap.cpp: include/python/cbsearch.i \
							include/python/identification.i \
							include/python/examples.i
		$(SWIG) $(AX_SWIG_PYTHON_OPT) -c++ -o $@ $<
python_PYTHON = $(builddir)/cbsearch.py
pyexec_LTLIBRARIES = _cbsearch.la
_cbsearch_la_SOURCES = $(builddir)/cbsearch_wrap.cpp include/python/cbsearch.hpp include/python/cbsearch.i \
						include/python/identification.hpp include/python/identification.i \
						include/python/examples.hpp include/python/examples.i
_cbsearch_la_LDFLAGS = -module ${PYTHON_LDFLAGS}
_cbsearch_la_LIBADD = libcbsearch.la
_cbsearch_la_CPPFLAGS = -I$(srcdir)/include ${PYTHON_CPPFLAGS}

EXTRA_DIST = src/tests/data/query_1_lcr.fasta \
                        src/tests/data/empty.txt \
                        src/tests/data/db_5_lcrs.fasta \
                        src/tests/data/output_1.txt \
                        example/LICENSE \
                        example/Q01560.fasta \
                        example/database.fasta


# [end] BUILD PYTHON PACKAGE



cbsearch_SOURCES = src/main.cpp
cbsearch_LDADD = libcbsearch.la


testcbsearch_SOURCES = src/tests/test.cpp \
 		include/tests/alignment/testalignmentprinter.hpp src/tests/alignment/testalignmentprinter.cpp \
 		include/tests/method/testnscsearch.hpp src/tests/method/testnscsearch.cpp \
 		include/tests/method/testresultsoutput.hpp src/tests/method/testresultsoutput.cpp \
 		include/tests/method/testoptions.hpp src/tests/method/testoptions.cpp \
		include/tests/dal/testsequencereaderfasta.hpp src/tests/dal/testsequencereaderfasta.cpp \
 		include/tests/utils/teststringutils.hpp src/tests/utils/teststringutils.cpp \
 		include/tests/utils/testfileutils.hpp src/tests/utils/testfileutils.cpp \
 		include/tests/utils/testnumericutils.hpp src/tests/utils/testnumericutils.cpp \
 		include/tests/utils/testfunctionutils.hpp src/tests/utils/testfunctionutils.cpp \
		include/tests/identification/testcompositionmatrix.hpp src/tests/identification/testcompositionmatrix.cpp \
		include/tests/identification/testcompositioncalculator.hpp src/tests/identification/testcompositioncalculator.cpp \
		include/tests/identification/testcompositionsimilarity.hpp src/tests/identification/testcompositionsimilarity.cpp \
		include/tests/identification/testfragmentextender.hpp src/tests/identification/testfragmentextender.cpp \
		include/tests/identification/testsequencefrequency.hpp src/tests/identification/testsequencefrequency.cpp \
		include/tests/identification/testsimicomp.hpp src/tests/identification/testsimicomp.cpp \
 		include/tests/unittest.hpp src/tests/unittest.cpp \
		include/tests/residue/testalphabetreduction.hpp src/tests/residue/testalphabetreduction.cpp \
 		include/tests/residue/testscoringmatrix.hpp src/tests/residue/testscoringmatrix.cpp \
 		include/tests/residue/testmatrixrecalculator.hpp src/tests/residue/testmatrixrecalculator.cpp \
		include/tests/filters/testkmer.hpp src/tests/filters/testkmer.cpp \
		include/tests/filters/testcomposition.hpp src/tests/filters/testcomposition.cpp \
		include/tests/filters/testshortword.hpp src/tests/filters/testshortword.cpp \
		include/tests/filters/testfilterpipeline.hpp src/tests/filters/testfilterpipeline.cpp \
 		include/tests/alignment/og/testonewayglobal.hpp src/tests/alignment/og/testonewayglobal.cpp \
 		include/tests/alignment/og/testoggapaffinitymatrices.hpp src/tests/alignment/og/testoggapaffinitymatrices.cpp \
 		include/tests/alignment/sw/testsmithwaterman.hpp src/tests/alignment/sw/testsmithwaterman.cpp \
 		include/tests/alignment/sw/testswgapaffinitymatrices.hpp src/tests/alignment/sw/testswgapaffinitymatrices.cpp \
 		include/tests/alignment/nw/testneedlemanwunsch.hpp src/tests/alignment/nw/testneedlemanwunsch.cpp \
 		include/tests/alignment/nw/testnwgapaffinitymatrices.hpp src/tests/alignment/nw/testnwgapaffinitymatrices.cpp

testcbsearch_LDADD = libcbsearch.la


test: testcbsearch unittests

unittests:
	./testcbsearch $(top_srcdir)


pythontest: $(builddir)/cbsearch.py
	test -L _cbsearch.so || ln -s .libs/_cbsearch.so _cbsearch.so
	export PYTHONPATH=(pwd)
	python -m unittest discover $(top_srcdir)/src/tests/python

	

	
	
