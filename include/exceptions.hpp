/*
 * exceptions.hpp
 *
 *  Created on: Mar 22, 2023
 *      Author: pjarnot
 */

#ifndef NSRCSEARCH_INCLUDE_EXCEPTIONS_HPP_
#define NSRCSEARCH_INCLUDE_EXCEPTIONS_HPP_

#include <stdexcept>
#include <iostream>


class NotImplemented : public std::logic_error
{
public:
    NotImplemented(std::string source_file, int source_line) : std::logic_error(source_file + ":" + std::to_string(source_line) + ": Function not yet implemented.\n") { /* std::cerr << "NotImplemented. File: " << source_file << ":" << source_line << std::endl; */ };
};

#define throw_not_implemented() throw NotImplemented(__FILE__, __LINE__)

class FileNotFound : public std::logic_error
{
public:
    FileNotFound(std::string file_path, std::string source_file, int source_line) : std::logic_error(source_file + ":" + std::to_string(source_line) + ": File " + file_path + " not found.\n" ) { /* std::cerr << "Could not find file in path: " << file_path << " File: " << source_file << ":" << source_line << std::endl; */ };
};

#define throw_file_not_found(file_path) throw FileNotFound(file_path, __FILE__, __LINE__)


#endif /* NSRCSEARCH_INCLUDE_EXCEPTIONS_HPP_ */
