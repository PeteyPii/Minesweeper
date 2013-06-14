#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Field.h"
#include "State.h"

class Field;

class GameState : public State
{
public:
	const static float infoTextSizeFactor;

	sf::Sprite background;
	sf::Text timeElapsedText, minesLeft;
	sf::Text timeElapsedTitle, minesLeftTitle;
	sf::Clock clock;
	bool gameBegan;
	sf::Time timeElapsed, totalIdleTime;
	Field field;
	bool leftButtonDown, rightButtonDown, middleButtonDown;
	bool inputReady;

	GameState();
	~GameState();

	virtual void step();
	virtual void draw();
	virtual void eventMouseMoved(sf::Event mouseEvent);
	virtual void eventMouseButtonPressed(sf::Event mouseEvent);
	virtual void eventMouseButtonReleased(sf::Event mouseEvent);
	virtual void eventKeyPressed(sf::Event keyEvent);

	void updateButtons(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMiddleDown);

	void newGame();
	void back();
};