#pragma once

#include <SFML/Graphics.hpp>

#include "Field.h"
#include "State.h"

class Field;

class GameState : public State
{
public:
	sf::Sprite background;
	Field field;
	bool leftButtonDown, rightButtonDown, middleButtonDown, firstMove;
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