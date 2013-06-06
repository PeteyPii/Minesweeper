#include "Field.h"

using namespace std;

// definitions of static constants
const unsigned char Field::mineChar = 15;		
const unsigned char Field::markedChar = 4;
const unsigned char Field::hiddenChar = 35;
const unsigned char Field::verticalDash = 186;
const unsigned char Field::horizontalDash = 205;
const unsigned char Field::marginSpacer = 249;

bool Field::revealSpot(int x, int y)
{
	if(!revealedSpaces[(uint)x][(uint)y] && !marked[x][y])	// the space is not marked or already revealed
	{
		revealedSpaces[(uint)x][(uint)y] = true;

		if(mines[(uint)x][(uint)y])	
			return true; // return true because a mine was revealed
		else if(numberOfNearbyMines[(uint)x][(uint)y] == 0)	// recursive check to reveal spaces around a a spot with zero nearby mines
		{
			for(int scanX = x - 1; scanX <= x + 1; ++scanX)
				for(int scanY = y - 1; scanY <= y + 1; ++scanY)
				{
					if(scanX < 0 || scanX >= (int)fieldWidth || scanY < 0 || scanY >= (int)fieldHeight)
						continue;

					revealSpot(scanX, scanY);
				}
		}
	}

	return false;
}
Field::Field(uint numberOfMines, uint fieldWidth, uint fieldHeight, int zeroAdjacentMinesLocationX, int zeroAdjacentMinesLocationY)
	: mines(fieldWidth, vector<bool>(fieldHeight, false)),
	revealedSpaces(fieldWidth, vector<bool>(fieldHeight, false)),
	marked(fieldWidth, vector<bool>(fieldHeight, false)),
	numberOfNearbyMines(fieldWidth, vector<int>(fieldHeight, 0)),
	numberOfMines(numberOfMines),
	fieldWidth(fieldWidth),
	fieldHeight(fieldHeight)
{
	bool firstSpotZero = false;
	if(zeroAdjacentMinesLocationX != -1 && zeroAdjacentMinesLocationY != -1)
		firstSpotZero = true;	// if the first location variables are not default, use them

	if(numberOfMines > fieldHeight * fieldWidth - 9 * (int)firstSpotZero)
		this->numberOfMines = fieldWidth * fieldHeight - 9 * (int)firstSpotZero;	// reduce the number of mines to a maximum base don the field

	if(this->numberOfMines < 0)
		this->numberOfMines = 0;	// blanket check to make sure the number of mines is not negative from the previous call

	for(uint count = 0; count < numberOfMines; ++count)	// loop that places all the mines in random positions except where the first reveal is (if it is set)
	{
		bool minePlaced = false;
		while(!minePlaced)
		{
			int randX = random() % fieldWidth;
			int randY = random() % fieldHeight;

			if(!mines[(uint)randX][(uint)randY])
			{
				if(firstSpotZero)
				{
					if((randX - zeroAdjacentMinesLocationX < -1 || randX - zeroAdjacentMinesLocationX > 1) || (randY - zeroAdjacentMinesLocationY < -1 || randY - zeroAdjacentMinesLocationY > 1))
					{
						mines[(uint)randX][(uint)randY] = true;
						minePlaced = true;
					}
				}
				else
				{
					mines[(uint)randX][(uint)randY] = true;
					minePlaced = true;
				}
			}
		}
	}

	for(uint x = 0; x < fieldWidth; ++x)	// calculate hte number of nearby mines for every nearby square
		for(uint y = 0; y < fieldHeight; ++y)
		{
			int nearbyMineCount = 0;

			for(int scanX = x - 1; scanX <= (int)x + 1; ++scanX)
				for(int scanY = y - 1; scanY <= (int)y + 1; ++scanY)
				{
					if(scanX < 0 || scanX >= (int)fieldWidth || scanY < 0 || scanY >= (int)fieldHeight)
						continue;

					if(mines[(uint)scanX][(uint)scanY])
						++nearbyMineCount;
				}

				numberOfNearbyMines[x][y] = nearbyMineCount;
		}

	if(firstSpotZero)
		revealSpot(zeroAdjacentMinesLocationX, zeroAdjacentMinesLocationY);	// reveal the first location, if wanted
}
void Field::markSpot(uint x, uint y)
{
	if(x >= 0 && x < fieldWidth && y >= 0 && y < fieldHeight)	// not out of bounds
		if(!revealedSpaces[x][y])								// space isn't already revealed
			marked[x][y] = !marked[x][y];						// change whether or not it's marked
}
bool Field::clearUnmarkedArea(uint x, uint y)	// returns true if a mine was revealed
{
	for(int scanX = x - 1; scanX <= (int)x + 1; ++scanX)	// go through the 3x3 area around a location and reveal unmarked squares
		for(int scanY = y - 1; scanY <= (int)y + 1; ++scanY)
		{
			if(scanX < 0 || scanX >= (int)fieldWidth || scanY < 0 || scanY >= (int)fieldHeight)
				continue;

			if(!revealedSpaces[(uint)scanX][(uint)scanY] && !marked[(uint)scanX][(uint)scanY])
				if(revealSpot(scanX, scanY))
					return true;
		}

		return false;
}
ostream& operator<<(ostream& os, const Field& field)
{
	os << ' ';	// out put the space in the top left corner
	for(uint x = 0; x < field.fieldWidth; ++x)	// output the top margin with a dash every 5 spaces
	{
		if(x % 5 == 0)
			os << Field::verticalDash;
		else
			os << Field::marginSpacer;
	}
	os << endl;
	for(uint y = 0; y < field.fieldHeight; ++y)
	{
		if(y % 5 == 0)
			os << Field::horizontalDash;	// output a dash every 5 spaces down
		else
			os << Field::marginSpacer;		// otherwise output a margin spacer

		for(uint x = 0; x < field.fieldWidth; ++x)
		{
			// check the state of the space and output the correct character
			if(field.revealedSpaces[x][y])
			{
				if(field.mines[x][y])
				{
					os << Field::mineChar;
				}
				else if(field.numberOfNearbyMines[x][y] == 0)
				{
					os << ' ';
				}
				else
				{
					os << field.numberOfNearbyMines[x][y];
				}
			}
			else
			{
				if(field.marked[x][y])
					os << Field::markedChar;
				else
					os << Field::hiddenChar;
			}
		}
		os << endl;
	}

	return os;
}
int Field::numberOfRevealedSpaces()
{
	// go through the field and check if a location has a mine
	int count = 0;
	for(uint x = 0; x < fieldWidth; ++x)
		for(uint y = 0; y < fieldHeight; ++y)
			if(revealedSpaces[x][y])
				++count;
	return count;
}
int Field::numberOfUnrevealedSpaces()
{
	// number of unrevealed spaces is the field area minus the number of revealed spaces
	return (int)fieldHeight * (int)fieldWidth - numberOfRevealedSpaces();
}