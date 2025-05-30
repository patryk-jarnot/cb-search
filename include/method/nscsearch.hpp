/*
 * lcrsearch.hpp
 *
 *  Created on: Sep 26, 2022
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_NSCSEARCH_HPP_
#define NSCSEARCH_INCLUDE_NSCSEARCH_HPP_


#include "method/options.hpp"
#include "method/resultsoutput.hpp"
#include "dal/sequencereader.hpp"
#include "model/sequence.hpp"
#include "model/fragment.hpp"
#include "model/results.hpp"
#include "model/resultsitem.hpp"
#include "utils/fasta.hpp"
#include "utils/threadpool.hpp"


namespace nscsearch {

	class NscSearch {
	public:
		NscSearch(Options *iopt, SequenceReader *idatabase_reader);
		~NscSearch();

//		void scan_queries_and_database(std::istream *query_stream);
//		void scan_queries_and_database_threads(std::istream *query_stream, int ithread_count);
//		void scan_database(fasta::Sequence* iquery_sequence, ThreadPool *ithread_pool, int ithread_count);

		results_t scan_database(Sequence &iquery_sequence);
//		void save_reported_record(std::string iquery, std::string imidline, std::string ihit_header, std::string ihit_sequence, int score, float identity, float similarity);

		void save_reported_record(std::string iquery, std::string imidline, std::string ihit_header,
				std::string ihit_sequence, float score, float simi_score, float identity, float similarity, int fragment_begin,
				int fragment_end);

//		void report_record(std::string iquery, std::string imidline, std::string ihit_header, std::string ihit_sequence, int score, float identity, float similarity);

		results_t get_results() { return results; }

	private:
		Options *opt;
		SequenceReader *database_reader;
//		int thread_count;
		results_t results;
		std::mutex results_append_mutex;

	};
}

#endif /* NSCSEARCH_INCLUDE_LCRSEARCH_HPP_ */
