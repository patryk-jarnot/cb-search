%{
#include "python/examples.hpp"
%}

struct example_result_t {
	int begin;
	int end;
};

namespace std {
  %template(vectori) vector<int>;
  %template(vector_example_result_t) vector<example_result_t>;
};

std::vector<example_result_t> take_strings_return_vector_of_struct(std::string iquery, std::string isequence);
std::vector<int> take_strings_return_vector_of_ints(std::string iquery, std::string isequence);
void take_strings(std::string iquery, std::string isequence);
void take_struct(example_result_t iexample_result);



