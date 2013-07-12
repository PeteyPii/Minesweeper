#pragma once

#include <SFML/Graphics.hpp>

#include "ClickableButton.h"
#include "ClickableText.h"
#include "Globals.h"
#include "State.h"

class SettingsState : public State
{
public:
	sf::Sprite background;
	sf::Text title;
	ClickableText applySettings, backToMenu, exitGame;
	uint fieldWidth, fieldHeight, numberOfMines;
	sf::Text fieldWidthTitle, fieldHeightTitle, numberOfMinesTitle;
	sf::Text fieldWidthText, fieldHeightText, numberOfMinesText;
	ClickableButton fieldWidthUpButton, fieldHeightUpButton, numberOfMinesUpButton;
	ClickableButton fieldWidthDownButton, fieldHeightDownButton, numberOfMinesDownButton;
	sf::RectangleShape fieldWidthBG, fieldHeightBG, numberOfMinesBG;
	sf::Text currentStatsTitle;
	sf::Text winPercentageText, numberOfWinsText, numberOfGamesText, bestTimeText, averageTimeText;
	sf::Text howToResetAllStatsText;
	bool leftButtonDown, controlDown, shiftDown, RDown;

	SettingsState();
	~SettingsState();

	virtual void step();
	virtual void draw();
	virtual void eventMouseMoved(sf::Event mouseEvent);
	virtual void eventMouseButtonPressed(sf::Event mouseEvent);
	virtual void eventMouseButtonReleased(sf::Event mouseEvent);
	virtual void eventKeyPressed(sf::Event keyEvent);

	void updateButtons(sf::Vector2f mousePosition, bool isLeftDown);

	void updateStatsText();

	void apply();
	void back();
};