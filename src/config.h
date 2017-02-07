#ifndef __CONFIG__
#define __CONFIG__

#include <map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Config
{
public:
	bool Load(const char* filename);
	std::string GetValue(string key);

	static const char* FILTER_TYPE;
	static const char* FILTER_DIRECTORY;
	static const char* RENDER_SCRIPT;
	static const char* RENDER_MODULE;
	static const char* FILTER_SCRIPT;
	static const char* OUTPUT_DIRECTORY;
	static const char* OUTPUT_FILE;
	static const char* EXPORTER_TYPE;
	static const char* IMAGE_WIDTH;
	static const char* IMAGE_HEIGHT;

private:

	void SetupDefaultValues();
	void AddAdditionalInternalValues();

	typedef map<std::string, std::string> ConfigData;
	ConfigData m_ConfigData;
};

#endif