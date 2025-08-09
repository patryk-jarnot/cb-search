%module cbsearch

%include "std_vector.i"
%include "std_string.i"

%include "examples.i"
%include "identification.i"

%{
#include "python/cbsearch.hpp"
%}

void example_hello();
void calculata_composition(std::string isequence);
