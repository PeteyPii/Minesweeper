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
	blank.loadFromFile("resources/images/blank.png");

	timesFont.loadFromFile("resources/fonts/times.ttf");
}

