#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "GameState.h"
#include "MainMenuState.h"
#include "SettingsState.h"
#include "State.h"

class MinesweeperApp
{
public:
	sf::RenderWindow window;
	bool keepRunning;
	std::auto_ptr<MainMenuState> mainMenuState;
	std::auto_ptr<SettingsState> settingsState;
	std::auto_ptr<GameState> gameState;
	State* currentState;

	~MinesweeperApp();

	void begin();
	void stop();

	static MinesweeperApp& getInstance();

private:
	MinesweeperApp();  

	MinesweeperApp(MinesweeperApp const&);	// do not implement
	void operator=(MinesweeperApp const&);	// do not implement
};
