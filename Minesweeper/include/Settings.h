#pragma once

#include <map>
#include <string>

class Settings
{
public:
	static std::map<std::string, int> settings;

	static void loadSettings();
	static void saveSettings();

	static unsigned int getFieldWidth();
	static unsigned int getFieldHeight();
	static unsigned int getNumberOfMines();
	static unsigned int getWindowWidth();
	static unsigned int getWindowHeight();

private:
	Settings();
	~Settings();
};
