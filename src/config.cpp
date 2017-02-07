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
const char* Config::IMAGE_WIDTH = "imagewidth";
const char* Config::IMAGE_HEIGHT = "imageheight";

bool Config::Load(const char* filename)
{
	SetupDefaultValues();

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

	AddAdditionalInternalValues();

	return true;
}

void Config::SetupDefaultValues()
{
	m_ConfigData[FILTER_TYPE] = "python";
	m_ConfigData[FILTER_DIRECTORY] = "./scripts";
	m_ConfigData[RENDER_SCRIPT] = "renderer.py";
	m_ConfigData[FILTER_SCRIPT] = "filter.py";
	m_ConfigData[OUTPUT_DIRECTORY] = ".";
	m_ConfigData[OUTPUT_FILE] = "output.ppm";
	m_ConfigData[EXPORTER_TYPE] = "ppm";
	m_ConfigData[IMAGE_WIDTH] = "320";
	m_ConfigData[IMAGE_HEIGHT] = "240";
	
	
}

void Config::AddAdditionalInternalValues()
{
	m_ConfigData[RENDER_MODULE] = StringHelper::StringUntilFirstOccurence(m_ConfigData[RENDER_SCRIPT], '.');
}

std::string Config::GetValue(string key)
{
	return m_ConfigData[key];
}