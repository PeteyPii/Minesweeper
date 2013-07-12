#pragma once

#include <SFML/Graphics.hpp>

#include "ClickableText.h"
#include "State.h"

class MainMenuState : public State
{
public:
	sf::Sprite background;
	sf::Text title;
	ClickableText playGame, gameSettings, exitGame;
	bool leftButtonDown;

	MainMenuState();
	~MainMenuState();

	virtual void step();
	virtual void draw();
	virtual void eventMouseMoved(sf::Event mouseEvent);
	virtual void eventMouseButtonPressed(sf::Event mouseEvent);
	virtual void eventMouseButtonReleased(sf::Event mouseEvent);
	virtual void eventKeyPressed(sf::Event keyEvent);

	void updateButtons(sf::Vector2f mousePosition, bool isLeftDown);

	void play();
	void settings();
	void exit();
};