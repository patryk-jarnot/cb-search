/*
 * shortword.cpp
 *
 *  Created on: Jan 12, 2025
 *      Author: pjarnot
 */

#include "filters/shortword.hpp"


using namespace nscsearch;
using namespace std;


bool ShortWordFilter::is_similar(std::string) {
	return false;
}

void ShortWordFilter::set_query(std::string iquery) {}
