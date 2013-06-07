#include "Settings.h"

#include <exception>
#include <fstream>
#include <sstream>

#include "Globals.h"

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
	settings.insert(pair<string, int>("fieldWidth", defaultFieldWidth));
	settings.insert(pair<string, int>("fieldHeight", defaultFieldHeight));
	settings.insert(pair<string, int>("numberOfMines", defaultNumberOfMines));
	settings.insert(pair<string, int>("windowWidth", defaultWindowWidth));
	settings.insert(pair<string, int>("windowHeight", defualtWindowHeight));

	Settings::saveSettings();	// save default values if they were not read from a file
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
uint Settings::getFieldWidth()
{
	return settings.find("fieldWidth")->second;
}
uint Settings::getFieldHeight()
{
	return settings.find("fieldHeight")->second;
}
uint Settings::getNumberOfMines()
{
	return settings.find("numberOfMines")->second;
}
uint Settings::getWindowWidth()
{
	return settings.find("windowWidth")->second;
}
uint Settings::getWindowHeight()
{
	return settings.find("windowHeight")->second;
}
