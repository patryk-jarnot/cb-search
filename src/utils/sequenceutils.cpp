/*
 * sequenceutils.cpp
 *
 *  Created on: Mar 29, 2026
 *      Author: pjarnot
 */
#include "utils/sequenceutils.hpp"

using namespace std;


namespace cbsearch {
	map<uint16_t, int> count_kmers(string *sequence) {
		map<uint16_t, int> kmers;
		for (size_t i=0; i<sequence->size()-1; i++) {
			uint16_t kmer = ((uint16_t)(*sequence)[i] << 8) | (uint16_t)(*sequence)[i+1];
			if (kmers.find(kmer) == kmers.end()) {
				kmers[kmer] = 1;
			}
			else {
				kmers[kmer]++;
			}
		}
		return kmers;
	}
}

