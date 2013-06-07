#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Clickable
{
public:
	sf::FloatRect rect;

	Clickable(sf::FloatRect rect = sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f)));
	~Clickable();

	virtual bool updateAndGetClicked(sf::Vector2f mousePosition, bool isLeftDown);
	virtual void unhovered();
	virtual void hovered();
	virtual void clicked();
	virtual void clickedOutside();
	void resetStates();

protected:
	bool wasClicked;
	bool wasHovered;
};

