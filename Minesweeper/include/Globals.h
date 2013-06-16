#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

#include "mtrand.h"

extern MTRand_int32 random;		// random unsigned integer generator (use random() to get a value)
typedef unsigned int uint;		// typedef for less clutter

const uint defaultFieldWidth = 16,	// default number of columns for a field
	defaultFieldHeight = 16,		// default number of rows for a field
	defaultNumberOfMines = 40,		// default number of mines for a field
	defaultWindowWidth = 512,
	defualtWindowHeight = 512;

const uint fieldMargin = 48;	// amount of space to have around the drawn field

void centerOrigin(sf::Text& text);		// shifts text over so it is center aligned
template <class T>
std::string numberToString(T number)
{
	std::stringstream converter;
	converter.precision(3);
	converter.setf(std::ios::fixed, std::ios::floatfield);
	converter << number;
	return converter.str();
}
void drawRectangle(sf::RenderTarget& target, sf::FloatRect rect, sf::Color colour);
template <class T> 
const T& min(const T& a, const T& b) 
{
	return !(b<a)?a:b;
}
template <class T> 
const T& max(const T& a, const T& b) 
{
	return !(b>a)?a:b;
}