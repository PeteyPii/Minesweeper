#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "mtrand.h"

extern MTRand_int32 random;		// random unsigned integer generator (use random() to get a value)
typedef unsigned int uint;		// typedef for less clutter

const uint defaultFieldWidth = 20,	// default number of columns for a field
	defaultFieldHeight = 20,		// default number of rows for a field
	defaultNumberOfMines = 25,		// default number of mines for a field
	defaultWindowWidth = 512,
	defualtWindowHeight = 512;

const uint fieldMargin = 48;	// amount of space to have around the drawn field

void centerOrigin(sf::Text& text);		// shifts text over so it is center aligned
std::string numberToString(uint number);
void drawRectangle(sf::RenderTarget &target, sf::FloatRect rect, sf::Color colour);