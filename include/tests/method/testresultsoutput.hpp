/*
 * testresultsoutput.hpp
 *
 *  Created on: Apr 7, 2023
 *      Author: pjarnot
 */

#ifndef NSCSEARCH_INCLUDE_TESTS_TESTRESULTSOUTPUT_HPP_
#define NSCSEARCH_INCLUDE_TESTS_TESTRESULTSOUTPUT_HPP_

namespace nscsearch {
class TestResultsOutput {
public:
	void run();

private:
	void initialize_data();

	void test_single_hit();
	void test_two_hits();

	void test_two_hits_sort_by_score();
	void test_two_hits_sort_by_identity();
	void test_two_hits_sort_by_similarity();

	void test_two_hits_filter_by_score();
	void test_two_hits_filter_by_identity();
	void test_two_hits_filter_by_similarity();

	void test_two_hits_limit_to_one();
	void test_two_hits_limit_to_two();

};
}

#endif /* NSCSEARCH_INCLUDE_TESTS_TESTRESULTSOUTPUT_HPP_ */
