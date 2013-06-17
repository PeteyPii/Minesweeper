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

	static unsigned int getNumberOfFieldGames(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines);
	static unsigned int getNumberOfFieldWins(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines);
	static float		getTotalFieldTime(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines);
	static float		getBestFieldTime(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines);

	static void setNumberOfFieldGames(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines, unsigned int numberOfGames);
	static void setNumberOfFieldWins(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines, unsigned int numberOfWins);
	static void setTotalFieldTime(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines, float totalFieldTime);
	static void setBestFieldTime(unsigned int fieldWidth, unsigned int fieldHeight, unsigned int numberOfMines, float bestFieldTime);

private:
	Settings();
	~Settings();
};
