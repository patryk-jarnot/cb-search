#AM_CXXFLAGS = -pedantic -Wall -std=c++11 -Iinclude -I$(top_srcdir)/include -DNDEBUG -O2 -pthread
#AM_CXXFLAGS = -g -rdynamic -pedantic -Wall -std=c++11 -I$(top_srcdir)/include -pthread
AM_CXXFLAGS = -g -fpic -Wall -std=c++11 -I$(top_srcdir)/include -pthread
AM_LDFLAGS =

ACLOCAL_AMFLAGS = -I m4 --install
all: libnscsearch.la nscsearch $(builddir)/nscsearch.py test

bin_PROGRAMS = nscsearch testnscsearch


lib_LTLIBRARIES = libnscsearch.la
libnscsearch_la_SOURCES = include/method/nscsearch.hpp src/method/nscsearch.cpp \
		include/constants.hpp \
		include/exceptions.hpp \
		include/python/examples.hpp src/python/examples.cpp \
		include/python/nscsearch.hpp src/python/nscsearch.cpp \
		include/python/identification.hpp src/python/identification.cpp \
		include/method/options.hpp src/method/options.cpp \
		include/method/resultsoutput.hpp src/method/resultsoutput.cpp \
		include/debug.hpp src/debug.cpp \
		include/model/resultsitem.hpp \
		include/model/results.hpp \
		include/model/sequence.hpp src/model/sequence.cpp \
		include/model/fragment.hpp src/model/fragment.cpp \
		include/model/matrixresidue.hpp src/model/matrixresidue.cpp \
		include/filters/shortword.hpp src/filters/shortword.cpp \
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
		include/alignment/alignmentprinter.hpp src/alignment/alignmentprinter.cpp \
		include/alignment/alignbase.hpp src/alignment/alignbase.cpp \
		include/alignment/sw/swgapaffinitymatrices.hpp src/alignment/sw/swgapaffinitymatrices.cpp \
		include/alignment/sw/smithwaterman.hpp src/alignment/sw/smithwaterman.cpp \
		include/alignment/og/oggapaffinitymatrices.hpp src/alignment/og/oggapaffinitymatrices.cpp \
		include/alignment/og/onewayglobal.hpp src/alignment/og/onewayglobal.cpp \
		include/alignment/nw/nwgapaffinitymatrices.hpp src/alignment/nw/nwgapaffinitymatrices.cpp \
		include/alignment/nw/needlemanwunsch.hpp src/alignment/nw/needlemanwunsch.cpp

	

# [begin] BUILD PYTHON PACKAGE
	
BUILT_SOURCES = $(builddir)/nscsearch.py $(builddir)/nscsearch_wrap.cpp

$(builddir)/nscsearch.py $(builddir)/nscsearch_wrap.cpp: include/python/nscsearch.i \
							include/python/identification.i \
							include/python/examples.i
		$(SWIG) $(AX_SWIG_PYTHON_OPT) -c++ -o $@ $<
python_PYTHON = $(builddir)/nscsearch.py
pyexec_LTLIBRARIES = _nscsearch.la
_nscsearch_la_SOURCES = $(builddir)/nscsearch_wrap.cpp include/python/nscsearch.hpp include/python/nscsearch.i \
						include/python/identification.hpp include/python/identification.i \
						include/python/examples.hpp include/python/examples.i
_nscsearch_la_LDFLAGS = -module ${PYTHON_LDFLAGS}
_nscsearch_la_LIBADD = libnscsearch.la
_nscsearch_la_CPPFLAGS = -I$(srcdir)/include ${PYTHON_CPPFLAGS}

#EXTRA_DIST = m4/NOTES

# [end] BUILD PYTHON PACKAGE



nscsearch_SOURCES = src/main.cpp
nscsearch_LDADD = libnscsearch.la


testnscsearch_SOURCES = src/tests/test.cpp \
 		include/tests/alignment/testalignmentprinter.hpp src/tests/alignment/testalignmentprinter.cpp \
 		include/tests/method/testnscsearch.hpp src/tests/method/testnscsearch.cpp \
 		include/tests/method/testresultsoutput.hpp src/tests/method/testresultsoutput.cpp \
 		include/tests/method/testoptions.hpp src/tests/method/testoptions.cpp \
		include/tests/dal/testsequencereaderfasta.hpp src/tests/dal/testsequencereaderfasta.cpp \
		include/tests/filters/testshortword.hpp src/tests/filters/testshortword.cpp \
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
 		include/tests/alignment/og/testonewayglobal.hpp src/tests/alignment/og/testonewayglobal.cpp \
 		include/tests/alignment/og/testoggapaffinitymatrices.hpp src/tests/alignment/og/testoggapaffinitymatrices.cpp \
 		include/tests/alignment/sw/testsmithwaterman.hpp src/tests/alignment/sw/testsmithwaterman.cpp \
 		include/tests/alignment/sw/testswgapaffinitymatrices.hpp src/tests/alignment/sw/testswgapaffinitymatrices.cpp \
 		include/tests/alignment/nw/testneedlemanwunsch.hpp src/tests/alignment/nw/testneedlemanwunsch.cpp \
 		include/tests/alignment/nw/testnwgapaffinitymatrices.hpp src/tests/alignment/nw/testnwgapaffinitymatrices.cpp

testnscsearch_LDADD = libnscsearch.la


test: testnscsearch unittests

unittests:
	./testnscsearch $(top_srcdir)


pythontest: $(builddir)/nscsearch.py
	test -L _nscsearch.so || ln -s .libs/_nscsearch.so _nscsearch.so
	export PYTHONPATH=(pwd)
	python -m unittest discover $(top_srcdir)/src/tests/python

	

	
	
