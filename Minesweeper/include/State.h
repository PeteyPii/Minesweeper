#pragma once

#include <SFML/Window.hpp>

class State
{
public:
	State();
	~State();
	
	virtual void runTextOnly();

	virtual void step();
	virtual void draw();

	virtual void eventMouseMoved(sf::Event mouseEvent);
	virtual void eventMouseButtonPressed(sf::Event mouseEvent);
	virtual void eventMouseButtonReleased(sf::Event mouseEvent);
	virtual void eventKeyPressed(sf::Event keyEvent);
	virtual void eventKeyReleased(sf::Event keyEvent);
	virtual void eventTextEntered(sf::Event textEvent);
	virtual void eventMouseWheelMoved(sf::Event mouseEvent);
	virtual void eventWindowResized(sf::Event windowEvent);
};
