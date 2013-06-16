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
	const static sf::Color backgroundColour;	// colour the numbers are drawn an top of
	const static sf::Color numberColours[10];
	const static sf::Color hoverColour, clickedColour;

	std::vector<std::vector<bool> > mines;				// true for a mine in the spot
	std::vector<std::vector<bool> > revealed;			// true for a revealed square
	std::vector<std::vector<bool> > marked;				// true for a space marked as a present mine
	std::vector<std::vector<int> > numberOfNearbyMines;
	std::vector<std::vector<ClickableButton> > buttonsLMB, buttonsRMB, buttonsMMB, buttonsVisual;
	std::vector<std::vector<sf::Text> > textNumbers;

	bool firstMove;
	unsigned int numberOfMines;		// number of mines present in the field
	unsigned int fieldWidth, fieldHeight;
	sf::RectangleShape background, hover;
	sf::Vector2f position;

	// class constructor
	// numberOfMines: number of mines present in the field
	// fieldWidth: the number of columns the field has
	// fieldHeight: the number of rows the field has
	// firstMoveZero: whether or not the first revealed square will have zero nearby mines, true for yes
	Field(unsigned int numberOfMines, unsigned int fieldWidth, unsigned int fieldHeight, bool firstMoveZero = false);

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

	// function that counts the number of marked squares on the field
	// return: number of squares on the field that are marked
	unsigned int numberOfDetectedMines();

	// function that counts the number of unmarked mines on the field
	// return: number of marked squares subtracted from the number of mines
	int numberOfUndetectedMines();

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

	// function that checks if enough spaces have been revealed for a victorious game
	// return: true if the game has been won, false otherwise
	bool isVictoryReached();

	// function that checks if a mine has been revealed for a unsuccessful game
	// return: true if a mine has been revealed, false otherwise
	bool isDefeatReached();

	// function that moves the sprites and everything else that is drawn by the field to a certain position
	// position: coordinates of the top left corner of the field
	void setFieldPosition(sf::Vector2f position);

	// see void setFieldPosition(sf::Vector2f positon)
	void setFieldPosition(float positionX, float positionY);

private:
	Field();	// private default constructor (cannot be used)

	void generateField(int zeroAdjacentMinesLocationX = -1, int zeroAdjacentMinesLocationY = -1);
};
