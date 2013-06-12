#pragma once

#include <ostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "ClickableButton.h"

class Field : public sf::Drawable
{
public:
	// constant characters for outputting special field squares
	const static unsigned char mineChar,	// displays a mine		
		markedChar,							// mark for a where a mine is
		hiddenChar,							// what to display for unrevealed squares
		verticalDash,						// dash for the top margin
		horizontalDash,						// dash for the bottom margin
		marginSpacer;						// character between the margin dashes

	std::vector<std::vector<bool> > mines;				// true for a mine in the spot
	std::vector<std::vector<bool> > revealed;			// true for a revealed square
	std::vector<std::vector<bool> > marked;				// true for a space marked as a present mine
	std::vector<std::vector<int> > numberOfNearbyMines;
	std::vector<std::vector<ClickableButton> > buttonsLMB, buttonsRMB, buttonsMMB, buttonsVisual;
	std::vector<std::vector<sf::Text> > textNumbers;

	unsigned int numberOfMines;		// number of mines present in the field
	unsigned int fieldWidth, fieldHeight;

	// class constructor
	// numberOfMines: number of mines present in the field
	// fieldWidth: the number of columns the field has
	// fieldHeight: the number of rows the field has
	// zeroAdjacentMinesLocationX: if set, the x-coordinate of where no mines will spawn near
	// zeroAdjacentMinesLocationY: if set, the y-coordinate of where no mines will spawn near
	Field(unsigned int numberOfMines, unsigned int fieldWidth, unsigned int fieldHeight, int zeroAdjacentMinesLocationX = -1, int zeroAdjacentMinesLocationY = -1);

	// function to reveal a location on the field
	// return: true if a mine is revealed
	// x: x-coordinate of location to reveal
	// x: y-coordinate of location to reveal
	bool revealSpot(int x, int y);

	// function to mark/unmark an unrevealed location on the field
	// x: x-coordinate of location to mark/unmark
	// y: y-coordinate of location to mark/unmark
	void markSpot(unsigned int x, unsigned int y);

	// function to reveal all unmarked locations adjacent to specified location
	// return: true if any of the spaces revealed contains a mine
	// x: x-coordinate of the location to clear around
	// y: y-coordinate of the location to clear around
	bool clearUnmarkedArea(unsigned int x, unsigned int y);

	// operator to output the field to a standard stream in text form
	// return: the ostream being output to
	// os: output stream for the field to be output to
	// field: field that is being output
	friend std::ostream& operator<<(std::ostream& os, const Field& field);

	// function that counts the number of spaces on the field that have been revealed
	// return: number of spaces on the field that have been revealed
	int numberOfRevealedSpaces();

	// function that counts the number of spaces on the field that have not been revealed
	// return: number of spaces on the field that have not been revealed
	int numberOfUnrevealedSpaces();

	// function that draws the field to a sf::RenderTarget
	// target: sf::RenderTarget that will be drawn on
	// renderStates: render states
	virtual void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const;

	// function that checks for all the squares of the field for clicks
	// mousePostion: where the mouse is on the field
	// isLeftDown: is the left mouse button pressed
	// isRightDown: is the right mouse button pressed
	// isMiddleDown: is the middle mouse button pressed
	void updateFieldClicks(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMiddleDown);

private:
	Field();	// private default constructor (cannot be used)
};
