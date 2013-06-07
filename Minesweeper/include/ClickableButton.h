#pragma once

#include "Clickable.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ClickableButton : public Clickable, public sf::Drawable
{
public:
	sf::Sprite sprite;

	ClickableButton(sf::Texture *texture = 0, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), sf::Vector2f size = sf::Vector2f(0.0f, 0.0f));
	~ClickableButton();

	virtual void unhovered();
	virtual void hovered();
	virtual void clicked();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

