/*
 * debug.cpp
 *
 *  Created on: Mar 29, 2023
 *      Author: pjarnot
 */

#include "debug.hpp"

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void stacktrace_handler(int sig) {
	void *array[10];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}


void subscribe_stacktrace(int idebug_level) {
	if (idebug_level > 0) {
		signal(SIGSEGV, stacktrace_handler);
	}
}


