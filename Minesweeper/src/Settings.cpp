#include "Settings.h"

#include <exception>
#include <fstream>
#include <sstream>

using namespace std;

std::map<std::string, int> Settings::settings;

Settings::Settings()
{

}
Settings::~Settings()
{

}
void Settings::loadSettings()
{
	ifstream settingsFile;
	settingsFile.open("settings.txt");

	while(settingsFile.good())
	{
		char line[256];
		settingsFile.getline(line, 256);

		if(line[0] == '\0' || line[0] == ' ' || line[0] == '\n')
		{
			continue;
		}

		string strLine(line), key, mapValue;

		size_t equalSign = strLine.find_first_of('=');

		if(equalSign == string::npos)
		{
			throw exception("Bad settings file");
		}

		key = strLine.substr(0, equalSign);
		mapValue = strLine.substr(equalSign + 1, strLine.size() - key.size() - 1);

		int number;
		stringstream converter;
		converter << mapValue;

		if(!(converter >> number))
		{
			throw exception("Bad settings value");
		}

		settings.insert(pair<string, int>(key, number));
	}

	settingsFile.close();

	// Default settings (they do not overwrite)
	settings.insert(pair<string, int>("textOnly", 0));
}
void Settings::saveSettings()
{
	ofstream settingsFile;
	settingsFile.open("settings.txt");

	if(settingsFile.is_open())
	{
		for(map<string, int>::iterator it = settings.begin(); it != settings.end(); it++)
		{
			settingsFile << it->first << '=' << it->second << endl;
		}

		settingsFile.close();
	}
	else
	{
		throw exception("Could not save settings");
	}
}
bool Settings::isGameTextOnly()
{
	if(settings.find("textOnly")->second != 0)	// "textOnly=1"
	{
		return true;
	}
	else
	{
		return false;
	}
}
