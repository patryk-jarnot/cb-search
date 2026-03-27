/*
 * stringhelper.cpp
 *
 *  Created on: Oct 4, 2022
 *      Author: pjarnot
 */

#include "utils/stringutils.hpp"

#include "debug.hpp"

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

//using namespace nscsearch;
using namespace std;


namespace nscsearch {

	std::string reverse_str(std::string &input_str) {
		return std::string(input_str.rbegin(), input_str.rend());
	}

	std::string limit_str(std::string &input_str, size_t imax_length) {
		size_t header_len = imax_length < input_str.length() ? imax_length : input_str.length();
		std::string retval = input_str.substr(0, header_len);
		if (header_len < input_str.length()) {
			retval = retval.replace(retval.end()-3, retval.end(), 3, '.');
		}
		return retval;
	}

	std::string replace_all_return(std::string const& istr, std::string const& iold_str, std::string const& inew_str) {
		std::string buff = istr;
		replace_all(buff, iold_str, inew_str);
		return buff;
	}

	void replace_all(std::string &io_str, std::string const& iold_str, std::string const& inew_str) {
	    std::string buf;
	    std::size_t pos = 0;
	    std::size_t prevPos;

	    // Reserves rough estimate of final size of string.
	    buf.reserve(io_str.size());

	    while (true) {
	        prevPos = pos;
	        pos = io_str.find(iold_str, pos);
	        if (pos == std::string::npos)
	            break;
	        buf.append(io_str, prevPos, pos - prevPos);
	        buf += inew_str;
	        pos += iold_str.size();
	    }

	    buf.append(io_str, prevPos, io_str.size() - prevPos);
	    io_str.swap(buf);
	}


	float jaccard_index(string *left, string *right) {
		static string* left_string;
		static map<char, int> left_count;
		static char amino_acids[] = {'A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V'};

		if (left != left_string) {
			left_string = left;
			left_count = map<char, int>();
			for (int i=0; i<20; i++) {
				char c = amino_acids[i];
				left_count[c] = 0;
			}
			for (char c : *left) {
//				if (left_count.find(c) == left_count.end()) {
//					left_count[c] = 0;
//				}
				left_count[c]++;
			}
		}

		map<char, int> right_count;

		for (int i=0; i<20; i++) {
			char c = amino_acids[i];
			right_count[c] = 0;
		}
		for (char c : *right) {
//			if (right_count.find(c) == right_count.end()) {
//				right_count[c] = 0;
//			}
			right_count[c]++;
		}

		int sum_residue_count = 0;
		int alternative_residue_count = 0;
		for (int i=0; i<20; i++) {
			char c = amino_acids[i];
			sum_residue_count += min(left_count[c], right_count[c]);
			alternative_residue_count += max(left_count[c], right_count[c]);
		}

		float retval = (float)sum_residue_count / alternative_residue_count;

		return retval;
	}

	std::vector<std::string> split(std::string s, const std::string& delimiter) {
		std::vector<std::string> tokens;
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			tokens.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		tokens.push_back(s);

		return tokens;
	}

	std::vector<std::string> split_regex(std::string &s, const std::string& delimiter) {
		std::vector<std::string> items;
//		std::regex rgx("\\s+");
		std::regex rgx(delimiter);
		std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
		std::sregex_token_iterator end;
		for ( ; iter != end; ++iter)
			items.push_back(*iter);
		return items;
	}

	void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
		}));
	}

	void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	void trim(std::string &s) {
		rtrim(s);
		ltrim(s);
	}

	std::string ltrim_copy(std::string s) {
		ltrim(s);
		return s;
	}

	std::string rtrim_copy(std::string s) {
		rtrim(s);
		return s;
	}

	std::string trim_copy(std::string s) {
		trim(s);
		return s;
	}

}


