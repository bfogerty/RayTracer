#ifndef __STRING_HELPER__
#define __STRING_HELPER__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class StringHelper
{
public:

	static void Split(char d, string text, vector<string> &lines);
	static void Join(char d, vector<string> &lines, string &text);
	static std::string TrimWhitespace(std::string & src, bool ignoreQuotes = false);
	static std::string TrimStartAndEndWhitespace(const std::string & src);
	static std::string ReplaceChar(const std::string & src, char charToReplace, char charToReplaceWith, bool ignoreQuotes = false);
	static std::string ToLower(std::string& src);
	static std::string StringUntilFirstOccurence(const std::string & src, char charToStopAt);
};

#endif