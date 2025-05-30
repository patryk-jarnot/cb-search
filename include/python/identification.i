%{
#include "python/identification.hpp"
%}

struct result_t {
	int begin;
	int end;
};

namespace std {
  %template(vectori) vector<int>;
  %template(vectorf) vector<float>;
  %template(vector_result_t) vector<result_t>;
};


std::vector<float> window_similarity_scores(std::string iquery, std::string isequence);
std::vector<result_t> identify(std::string iquery, std::string isequence, float ithreshold);
