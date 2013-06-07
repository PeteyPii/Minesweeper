#include "Clickable.h"

Clickable::Clickable(sf::FloatRect rect)
{
	this->rect = rect;
}
Clickable::~Clickable()
{

}
bool Clickable::updateAndGetClicked(sf::Vector2f mousePosition, bool isLeftDown)
{
	if(rect.contains(mousePosition.x, mousePosition.y))	// Mouse is over the clicking area
	{
		if(wasClicked)
		{
			if(!isLeftDown)	// Clicked and released inside the clicking area
			{
				wasHovered = true;
				wasClicked = false;
				hovered();

				return true;
			}
		}
		else
		{
			if(isLeftDown)	// Clicked in the clicking area
			{
				wasClicked = true;
				clicked();
			}
			else if(!wasHovered)
			{
				wasHovered = true;
				hovered();
			}
		}
	}
	else	// Mouse is not over the clicking area
	{
		if(wasHovered || wasClicked)
		{
			wasClicked = false;
			wasHovered = false;
			unhovered();
		}

		if(isLeftDown)
		{
			clickedOutside();
		}
	}

	return false;
}
void Clickable::unhovered()
{

}
void Clickable::hovered()
{

}
void Clickable::clicked()
{

}
void Clickable::clickedOutside()
{

}
void Clickable::resetStates()
{
	wasClicked = false;
	wasHovered = false;
	unhovered();
}
