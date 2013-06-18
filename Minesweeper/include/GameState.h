#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Field.h"
#include "State.h"

class Field;

class GameState : public State
{
public:
	const static float infoTextSizeFactor, gameOverTextFactor, statsTextSizeFactor;

	sf::Sprite background;
	sf::Text timeElapsedText, minesLeft;
	sf::Text timeElapsedTitle, minesLeftTitle;
	sf::Clock clock;
	bool gameBegan, windowFocused;
	sf::Time timeElapsed;
	Field field;
	bool leftButtonDown, rightButtonDown, middleButtonDown;
	bool inputReady;
	bool isVictory, isDefeat;
	sf::Text playAgainText, victoryText, defeatText;
	sf::Text lastTimeText, winPercentageText, numberOfWinsText, numberOfGamesText, bestTimeText, averageTimeText;
	sf::RectangleShape backgroundShade;

	GameState();
	~GameState();

	virtual void step();
	virtual void draw();
	virtual void eventMouseMoved(sf::Event mouseEvent);
	virtual void eventMouseButtonPressed(sf::Event mouseEvent);
	virtual void eventMouseButtonReleased(sf::Event mouseEvent);
	virtual void eventKeyPressed(sf::Event keyEvent);
	virtual void eventMouseExited();
	virtual void eventWindowUnfocused();
	virtual void eventWindowFocused();

	void updateButtons(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMiddleDown);
	void updateStatsTexts();

	void newGame();
	void back();
};