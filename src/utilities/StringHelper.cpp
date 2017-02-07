#include "StringHelper.h"

void StringHelper::Split(char d, string text, vector<string> &lines)
{
	unsigned int index = 0;
	for (;;)
	{
		int endIndex = text.find_first_of(d, index);
		if (endIndex < 0)
		{
			unsigned int length = text.length() - index;
			string e = text.substr(index, length);
			if (e != "")
			{
				lines.push_back(e);
			}
			break;
		}
		unsigned int length = endIndex - index;
		string e = text.substr(index, length);
		index = endIndex + 1;
		if (e != "")
		{
			lines.push_back(e);
		}
	}
}
void StringHelper::Join(char d, vector<string> &lines, string &text)
{
	vector<string>::iterator it = lines.begin();
	do
	{
		text = text + *it + d;
		++it;
	} while (it != lines.end() - 1);
	text = text + *it;
}

// Make a string only have single spaces.
std::string StringHelper::TrimWhitespace(std::string & src, bool ignoreQuotes)
{
	std::string dst;

	if (src.length() <= 0)
	{
		return dst;
	}

	bool append = true;
	bool inAQuote = false;
	for (std::string::iterator i = src.begin(); i != src.end(); ++i)
	{
		if (ignoreQuotes)
		{
			if (*i == '\"')
			{
				inAQuote = !inAQuote;

				if (inAQuote)
				{
					append = true;
				}
			}
		}

		if (*i != ' ')
		{
			append = true;
		}

		if (append)
		{
			dst = dst + *i;
		}

		if (*i == ' ' && !inAQuote)
		{
			append = false;
			continue;
		}

	}

	return dst;
}

std::string StringHelper::TrimStartAndEndWhitespace(const std::string & src)
{
	std::string dst;

	if (src.length() <= 0)
	{
		return dst;
	}

	int stringStart = -1;
	int stringEnd = -1;

	for (int i = 0; i < src.length(); ++i)
	{
		if (src[i] != ' ')
		{
			stringStart = i;
			break;
		}
	}


	for (int i = src.length() - 1; i >= 0; --i)
	{
		if (src[i] != ' ')
		{
			stringEnd = i;
			break;
		}
	}

	if (stringStart < 0 || stringEnd < 0)
	{
		return dst;
	}

	dst = src.substr(stringStart, (stringEnd+1) - stringStart);

	return dst;
}

std::string StringHelper::ReplaceChar(const std::string & src, char charToReplace, char charToReplaceWith, bool ignoreQuotes)
{
	std::string dst = src;

	if (src.length() <= 0)
	{
		return dst;
	}

	if (charToReplace == charToReplaceWith)
	{
		return dst;
	}

	bool inAQuote = false;
	for (int i = 0; i < dst.length(); ++i)
	{
		if (ignoreQuotes)
		{
			if (dst[i] == '\"')
			{
				inAQuote = !inAQuote;
			}
		}

		if (dst[i] == charToReplace && !inAQuote)
		{
			dst[i] = charToReplaceWith;
		}
	}

	return dst;
}

std::string StringHelper::ToLower(std::string& src)
{
	std::string result = src;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);

	return result;
}

std::string StringHelper::StringUntilFirstOccurence(const std::string & src, char charToStopAt)
{
	int endString = src.find(charToStopAt);
	std::string result = src.substr(0, endString);

	return result;
}
