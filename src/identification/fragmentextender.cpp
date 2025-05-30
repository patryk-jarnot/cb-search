/*
 * fragmentextender.cpp
 *
 *  Created on: May 19, 2023
 *      Author: pjarnot
 */


#include "identification/fragmentextender.hpp"

#include "debug.hpp"


namespace nscsearch {

	void FragmentExtender::extend_fragment(int *iobegin, int *ioend, std::vector<float> &smoothed_scores) {
		int query_length = *ioend - *iobegin + 1;
		int new_end = *ioend;

		for (int i=*iobegin; i<(int)smoothed_scores.size() && smoothed_scores[i] >= smoothed_scores[*iobegin-1]; i++) {
			new_end = i+query_length;
		}
		*ioend = new_end;

		int new_begin = *iobegin;
		for (int i=*iobegin-2; i>=0 && smoothed_scores[i] >= smoothed_scores[*iobegin-1]; i--) {
			new_begin = i+1;
		}
		*iobegin = new_begin;
	}

}

