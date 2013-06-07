#include "Globals.h"

#include <ctime>

extern MTRand_int32 random((unsigned long)time(0));

void centerOrigin(sf::Text& text)
{
	text.setOrigin(0.5f * text.getLocalBounds().width, 0.5f * text.getLocalBounds().height);
}
