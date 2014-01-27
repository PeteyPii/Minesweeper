#include "Resources.h"

Resources::Resources()
{

}
Resources::~Resources()
{

}
Resources& Resources::getInstance()
{
	static Resources instance;	// guaranteed to be destroyed
								// instantiated on first use
	return instance;
}
void Resources::loadResources()
{
	background.loadFromFile("resources/images/background.png");
	mine.loadFromFile("resources/images/mine.png");
	mark.loadFromFile("resources/images/mark.png");
	area.loadFromFile("resources/images/area.png");
	invisibleButton.loadFromFile("resources/images/blank.png");
	upButton.loadFromFile("resources/images/arrowUp.png");
	downButton.loadFromFile("resources/images/arrowDown.png");

	timesFont.loadFromFile("resources/fonts/times.ttf");
	squareFont.loadFromFile("resources/fonts/Square.ttf");

	setSmooth(true);
}

void Resources::setSmooth(bool isSmooth)
{
	background.setSmooth(true);
	mine.setSmooth(true);
	mark.setSmooth(true);
	area.setSmooth(true);
	invisibleButton.setSmooth(true);
	upButton.setSmooth(true);
	downButton.setSmooth(true);
}

