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

	timesFont.loadFromFile("resources/fonts/times.ttf");
}

