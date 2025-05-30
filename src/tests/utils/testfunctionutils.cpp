/*
 * testfunctionutils.cpp
 *
 *  Created on: May 18, 2023
 *      Author: pjarnot
 */

#include "tests/utils/testfunctionutils.hpp"

#include "utils/functionutils.hpp"

#include "tests/unittest.hpp"

#include <iostream>
#include <vector>
#include <algorithm>


using namespace nscsearch;
using namespace std;


void TestFunctionUtils::run() {
	initialize_data();

	smooth_data_flat();
	smooth_data_single_outlier();
	smooth_data_real_function();

	std::cerr << "\n";
}


void TestFunctionUtils::initialize_data() {

}


void TestFunctionUtils::smooth_data_flat() {
	std::vector<float> function_data {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

	std::vector<float> smoothed_function_data = moving_average(function_data, 2);

	ASSERT(equal(smoothed_function_data.begin(), smoothed_function_data.end(), function_data.begin()));
}


void TestFunctionUtils::smooth_data_single_outlier() {
	std::vector<float> function_data    {2,2,2,2,2,2,4    ,2,    2,2,2,2,2,2,2,2,2,2,2};
	std::vector<float> expected_results {2,2,2,2,2,2,8.0/3,8.0/3,8.0/3,2,2,2,2,2,2,2,2,2,2};

	std::vector<float> smoothed_function_data = moving_average(function_data, 2);

	ASSERT(equal(smoothed_function_data.begin(), smoothed_function_data.end(), expected_results.begin()));
}


void TestFunctionUtils::smooth_data_real_function() {
	std::vector<float> function_data {4, 4, 4, 4, 4, 11, 19, 27, 27, 35, 40, 47, 46, 55, 47, 40, 32, 32, 24, 18, 9, 13, 4, 4, 4, 4};
	std::vector<float> expected_results {4, 4, 4, 4, 4, 19.0/3, 34.0/3, 57.0/3, 73.0/3, 89.0/3, 102.0/3, 122.0/3, 133.0/3, 148.0/3, 148.0/3, 142.0/3, 119.0/3, 104.0/3, 88.0/3, 74.0/3, 51.0/3, 40.0/3, 26.0/3, 21.0/3, 4, 4};

	std::vector<float> smoothed_function_data = moving_average(function_data, 2);

//	for (int i=0; i<smoothed_function_data.size(); i++) {
//		cout << smoothed_function_data[i] << " ";
//	}
//	cout << "\n";
//	for (int i=0; i<expected_results.size(); i++) {
//		cout << expected_results[i] << " ";
//	}
//	cout << "\n";

	ASSERT(equal(smoothed_function_data.begin(), smoothed_function_data.end(), expected_results.begin()));
}





