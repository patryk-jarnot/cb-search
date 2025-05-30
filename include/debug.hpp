/*
 * debug.hpp
 *
 *  Created on: Mar 22, 2023
 *      Author: pjarnot
 */

#ifndef NDEBUG

#include <chrono>
#include <iostream>

//std::cerr << "\033[32m" << UNIT_TESTS_PASSED_COUNTER << " asserts passed\033[39;49m, and \033[31m" << UNIT_TESTS_FAILED_COUNTER << " asserts failed\033[39;49m.\n\n";

#define DEBUG(MESSAGE) std::cerr << "[DEB]\033[36m " << __FILE__ << "\033[39;49m:\033[35m" << __FUNCTION__ << "\033[39;49m:\033[36m" << __LINE__ << "\033[39;49m:" << MESSAGE << std::endl; std::cerr.flush();
#define WARNING(MESSAGE) std::cerr << "[WAR]\033[36m " << __FILE__ << "\033[39;49m:\033[35m" << __FUNCTION__ << "\033[39;49m:\033[36m" << __LINE__ << "\033[39;49m:" << MESSAGE << std::endl; std::cerr.flush();
#define INFO(MESSAGE) std::cerr << "[INF]\033[36m " << __FILE__ << "\033[39;49m:\033[35m" << __FUNCTION__ << "\033[39;49m:\033[36m" << __LINE__ << "\033[39;49m:" << MESSAGE << std::endl; std::cerr.flush();


#define MEASURE_TIME_BEGIN() auto t1 = std::chrono::high_resolution_clock::now();
#define MEASURE_TIME_END() auto t2 = std::chrono::high_resolution_clock::now(); DEBUG(  std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() );

#define MEASURE_TIME_BEGIN_NEXT() t1 = std::chrono::high_resolution_clock::now();
#define MEASURE_TIME_END_NEXT() t2 = std::chrono::high_resolution_clock::now(); DEBUG(  std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() );


#else

#define DEBUG(MESSAGE)
#define WARNING(MESSAGE)
#define INFO(MESSAGE)


#define MEASURE_TIME_BEGIN()
#define MEASURE_TIME_END()

#define MEASURE_TIME_BEGIN_NEXT()
#define MEASURE_TIME_END_NEXT()

#endif /* NDEBUG_ */



void subscribe_stacktrace(int idebug_level);


