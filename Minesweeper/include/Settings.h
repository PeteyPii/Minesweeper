#pragma once

#include <map>
#include <string>

class Settings
{
public:
	static std::map<std::string, int> settings;

	static void loadSettings();
	static void saveSettings();

	static bool isGameTextOnly();

private:
	Settings();
	~Settings();
};
