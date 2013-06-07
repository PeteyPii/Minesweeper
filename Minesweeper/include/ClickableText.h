#pragma once

#include "Clickable.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

class ClickableText : public sf::Drawable, public Clickable
{
public:
	static sf::Color normalColour;
	static sf::Color hoverColour;
	static sf::Color clickedColour;

	sf::Text text;
	float borderSize;

	ClickableText(std::string text = "", sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), unsigned int fontSize = 12, sf::Font* font = 0, float borderSize = 0.0);
	~ClickableText();

	virtual void unhovered();
	virtual void hovered();
	virtual void clicked();
	void updateBoundingBox();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
