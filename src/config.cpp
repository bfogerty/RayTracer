#include "config.h"
#include "utilities/StringHelper.h"
#include <vector>

const char* Config::FILTER_TYPE = "filtertype";
const char* Config::FILTER_DIRECTORY = "filterdirectory";
const char* Config::RENDER_SCRIPT = "renderscript";
const char* Config::RENDER_MODULE = "rendermodule";
const char* Config::FILTER_SCRIPT = "filterscript";
const char* Config::OUTPUT_DIRECTORY = "outputdirectory";
const char* Config::OUTPUT_FILE = "outputfile";
const char* Config::EXPORTER_TYPE = "exporter";

bool Config::Load(const char* filename)
{
	std::string test = " Hello World";
	test = StringHelper::TrimStartAndEndWhitespace(test);

	std::string line;
	std::ifstream file(filename);
	while (!file.eof())
	{
		getline(file, line, '\n');
		std::string lineOfText = StringHelper::TrimStartAndEndWhitespace(line);
		
		vector<std::string> stringArray;
		StringHelper::Split('=', lineOfText, stringArray);
		std::string key = StringHelper::ToLower(StringHelper::TrimStartAndEndWhitespace(stringArray[0]));
		std::string value = StringHelper::TrimStartAndEndWhitespace(stringArray[1]);

		if (value[0] != '\"')
		{
			value = StringHelper::ToLower(value);
		}
		else
		{
			value = StringHelper::ReplaceChar(value, '\"', ' ');
			value = StringHelper::TrimStartAndEndWhitespace(value);
		}

		m_ConfigData[key] = value;
	}
	file.close();

	m_ConfigData[RENDER_MODULE] = StringHelper::StringUntilFirstOccurence(m_ConfigData[RENDER_SCRIPT], '.');

	return true;
}

std::string Config::GetValue(string key)
{
	return m_ConfigData[key];
}