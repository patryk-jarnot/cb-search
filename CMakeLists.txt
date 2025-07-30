cmake_minimum_required(VERSION 3.18)
project(nscsearch VERSION 1.0.1 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Options
option(BUILD_TESTING "Build tests" ON)

# Compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -fpic -Wall -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "-fpic -Wall -DNDEBUG -O2 -pthread")

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(SWIG 4.0 REQUIRED)
find_package(Threads REQUIRED)

# Look for Boost (matching original dependencies)
find_package(Boost QUIET)
if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
endif()

# Check for SWIG Python support
include(UseSWIG)

# Generate config header (replaces autotools config-nscsearch.h)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)

# Check for pthread support
if(Threads_FOUND)
    set(HAVE_PTHREAD 1)
endif()

# Check for Python development headers
if(Python3_Development_FOUND)
    set(HAVE_PYTHON3_DEV 1)
endif()

# Check for SWIG
if(SWIG_FOUND)
    set(HAVE_SWIG 1)
endif()

# Create config header similar to autotools
configure_file(
    ${CMAKE_SOURCE_DIR}/config-nscsearch.h.in
    ${CMAKE_BINARY_DIR}/include/config-nscsearch.h
    @ONLY
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include)

# Define source files for the main library
set(LIBNSCSEARCH_SOURCES
    src/method/nscsearch.cpp
    src/python/examples.cpp
    src/python/nscsearch.cpp
    src/python/identification.cpp
    src/method/options.cpp
    src/method/resultsoutput.cpp
    src/debug.cpp
    src/model/sequence.cpp
    src/model/fragment.cpp
    src/model/matrixresidue.cpp
    src/filters/shortword.cpp
    src/dal/sequencereader.cpp
    src/dal/sequencereaderfasta.cpp
    src/dal/sequencereaderstub.cpp
    src/utils/threadpool.cpp
    src/utils/fasta.cpp
    src/utils/stringutils.cpp
    src/utils/fileutils.cpp
    src/utils/functionutils.cpp
    src/utils/numericutils.cpp
    src/residue/scoringmatrix.cpp
    src/residue/matrixrecalculator.cpp
    src/residue/alphabetreduction.cpp
    src/identification/compositioncalculator.cpp
    src/identification/compositionmatrix.cpp
    src/identification/compositionsimilarity.cpp
    src/identification/simicomp.cpp
    src/identification/frequencyidentificator.cpp
    src/identification/fragmentextender.cpp
    src/identification/sequencefrequency.cpp
    src/alignment/alignmentprinter.cpp
    src/alignment/alignbase.cpp
    src/alignment/sw/swgapaffinitymatrices.cpp
    src/alignment/sw/smithwaterman.cpp
    src/alignment/og/oggapaffinitymatrices.cpp
    src/alignment/og/onewayglobal.cpp
    src/alignment/nw/nwgapaffinitymatrices.cpp
    src/alignment/nw/needlemanwunsch.cpp
)

# Create shared library
add_library(nscsearch SHARED ${LIBNSCSEARCH_SOURCES})
target_link_libraries(nscsearch PRIVATE Threads::Threads)

# Link Boost if found (matching original dependencies)
if(Boost_FOUND)
    target_link_libraries(nscsearch PRIVATE Boost::boost)
endif()

# Create main executable
add_executable(nscsearch_bin src/main.cpp)
target_link_libraries(nscsearch_bin PRIVATE nscsearch)
set_target_properties(nscsearch_bin PROPERTIES OUTPUT_NAME nscsearch)

# Test sources
set(TEST_SOURCES
    src/tests/test.cpp
    src/tests/alignment/testalignmentprinter.cpp
    src/tests/method/testnscsearch.cpp
    src/tests/method/testresultsoutput.cpp
    src/tests/method/testoptions.cpp
    src/tests/dal/testsequencereaderfasta.cpp
    src/tests/filters/testshortword.cpp
    src/tests/utils/teststringutils.cpp
    src/tests/utils/testfileutils.cpp
    src/tests/utils/testnumericutils.cpp
    src/tests/utils/testfunctionutils.cpp
    src/tests/identification/testcompositionmatrix.cpp
    src/tests/identification/testcompositioncalculator.cpp
    src/tests/identification/testcompositionsimilarity.cpp
    src/tests/identification/testfragmentextender.cpp
    src/tests/identification/testsequencefrequency.cpp
    src/tests/identification/testsimicomp.cpp
    src/tests/unittest.cpp
    src/tests/residue/testalphabetreduction.cpp
    src/tests/residue/testscoringmatrix.cpp
    src/tests/residue/testmatrixrecalculator.cpp
    src/tests/alignment/og/testonewayglobal.cpp
    src/tests/alignment/og/testoggapaffinitymatrices.cpp
    src/tests/alignment/sw/testsmithwaterman.cpp
    src/tests/alignment/sw/testswgapaffinitymatrices.cpp
    src/tests/alignment/nw/testneedlemanwunsch.cpp
    src/tests/alignment/nw/testnwgapaffinitymatrices.cpp
)

# Create test executable (only if testing is enabled)
if(BUILD_TESTING)
    add_executable(testnscsearch ${TEST_SOURCES})
    target_link_libraries(testnscsearch PRIVATE nscsearch)

    # Enable testing
    enable_testing()
    add_test(NAME unittests COMMAND testnscsearch ${CMAKE_SOURCE_DIR})
endif()

# SWIG Python bindings
set_property(SOURCE include/python/nscsearch.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE include/python/nscsearch.i PROPERTY SWIG_MODULE_NAME nscsearch)

# Configure SWIG
swig_add_library(nscsearch_python
    TYPE SHARED
    LANGUAGE python
    SOURCES include/python/nscsearch.i
)

# Set properties for SWIG module
set_property(TARGET nscsearch_python PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)
target_include_directories(nscsearch_python PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${Python3_INCLUDE_DIRS}
)

target_link_libraries(nscsearch_python PRIVATE 
    nscsearch
    ${Python3_LIBRARIES}
)

# Set output name for Python module
set_target_properties(nscsearch_python PROPERTIES 
    OUTPUT_NAME _nscsearch
    PREFIX ""
)

# If on Linux/Unix, remove the 'lib' prefix and set .so extension
if(UNIX)
    set_target_properties(nscsearch_python PROPERTIES
        PREFIX ""
        SUFFIX ".so"
    )
endif()

# Find Threads package for pthread support (moved up since it's used earlier)
# find_package(Threads REQUIRED) # Already found above

# Installation
install(TARGETS nscsearch nscsearch_bin
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install Python module - handle both development and system install
# This mimics the original makeFlags behavior: pythondir=\${out}/${python3.sitePackages}
if(DEFINED ENV{out})
    # When building with Nix, use the Nix-provided Python site-packages path
    set(PYTHON_INSTALL_DIR "$ENV{out}/${Python3_SITEARCH}")
else()
    # For regular builds, use the standard Python site-packages
    set(PYTHON_INSTALL_DIR ${Python3_SITEARCH})
endif()

install(TARGETS nscsearch_python
    LIBRARY DESTINATION ${PYTHON_INSTALL_DIR}
)

# Install Python wrapper
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/nscsearch.py
    DESTINATION ${PYTHON_INSTALL_DIR}
)

# Install headers (optional, if you want to distribute the library)
install(DIRECTORY include/
    DESTINATION include/nscsearch
    FILES_MATCHING PATTERN "*.hpp"
    PATTERN "tests" EXCLUDE
    PATTERN "python" EXCLUDE
)

# Install example files
install(DIRECTORY example/
    DESTINATION share/nscsearch/example
)

# Install test data
install(DIRECTORY src/tests/data/
    DESTINATION share/nscsearch/test_data
)

# Custom target to run tests (only if testing is enabled)
if(BUILD_TESTING)
    add_custom_target(check
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS testnscsearch
        COMMENT "Running tests"
    )

    # Custom target for Python tests
    add_custom_target(pythontest
        COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}
                ${Python3_EXECUTABLE} -m unittest discover ${CMAKE_SOURCE_DIR}/src/tests/python
        DEPENDS nscsearch_python
        COMMENT "Running Python tests"
    )
endif()

# Print configuration summary
message(STATUS "Configuration Summary:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Python executable: ${Python3_EXECUTABLE}")
message(STATUS "  Python version: ${Python3_VERSION}")
message(STATUS "  SWIG executable: ${SWIG_EXECUTABLE}")
message(STATUS "  SWIG version: ${SWIG_VERSION}")
