#include "Clickable.h"

int Clickable::doubleClickTime = 250;

Clickable::Clickable(sf::FloatRect rect)
{
	this->rect = rect;
	resetStates();
}
Clickable::~Clickable()
{

}
Clickable::ClickType Clickable::updateAndGetClicked(sf::Vector2f mousePosition, bool isLeftDown)
{
	if(rect.contains(mousePosition.x, mousePosition.y))	
	{
		if(isLeftDown)
		{
			if(!wasClicked)	
			{
				wasClicked = true;
				clicked();
			}
		}
		else
		{
			if(wasClicked)
			{
				if(isClickReady)
				{
					wasClicked = false;
					hovered();

					if(doubleClicking && doubleClickTime != 0 && doubleClickTimer.restart().asMilliseconds() < doubleClickTime)
					{
						doubleClicking = false;
						return DOUBLE_CLICKED;
					}
					else
					{
						if(doubleClickTime != 0)
						{
							doubleClicking = true;
							doubleClickTimer.restart();
						}
						
						return CLICKED;
					}
				}
				else
				{
					wasClicked = false;
					isClickReady = true;
					hovered();
				}
			}
			else
			{
				if(!wasInside)
				{
					hovered();
				}
			}
		}

		wasInside = true;
	}
	else	
	{
		if(isLeftDown)
		{
			if(!wasClicked)
			{
				wasClicked = true;
				isClickReady = false;
			}
		}
		else
		{
			if(wasClicked)
			{
				wasClicked = false;
				isClickReady = true;
				clickedOutside();
			}
		}

		if(wasInside)
		{
			wasInside = false;
			unhovered();
		}
	}

	return NO_CLICK;
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
	doubleClicking = false;
	wasClicked = false;
	wasInside = false;
	isClickReady = true;
	unhovered();
}
