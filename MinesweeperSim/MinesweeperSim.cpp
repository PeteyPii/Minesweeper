#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

#include "mtrand.h"
#include "StreamInput.h"

MTRand_int32 random((unsigned long)time(0));

using namespace std;
typedef unsigned int uint;					// typedef for faster typing
const unsigned char mineChar = 15,			// constant characters for outputting special squares
	markedChar = 4, 
	hiddenChar = 35,
	verticalDash = 186,
	horizontalDash = 205,
	marginSpacer = 249;		
const uint defaultFieldWidth = 30,
	defaultFieldHeight = 16,
	defaultNumberOfMines = 99;

class Field
{
public:
	vector<vector<bool> > mines;			// true for a mine in the spot
	vector<vector<bool> > revealedSpaces;	// true for a revealed square
	vector<vector<bool> > marked;			// true for a space marked as a present mine
	vector<vector<int> > numberOfNearbyMines;

	uint numberOfMines;
	uint fieldWidth, fieldHeight;

	bool revealSpot(int locX, int locY)	// returns true when a mine is hit
	{
		marked[(uint)locX][(uint)locY] = false;
		if(!revealedSpaces[(uint)locX][(uint)locY] && !marked[locX][locY])
		{
			revealedSpaces[(uint)locX][(uint)locY] = true;

			if(mines[(uint)locX][(uint)locY])
				return true;
			else
				if(numberOfNearbyMines[(uint)locX][(uint)locY] == 0)
				{
					for(int scanX = locX - 1; scanX <= locX + 1; ++scanX)
						for(int scanY = locY - 1; scanY <= locY + 1; ++scanY)
						{
							if(scanX < 0 || scanX >= (int)fieldWidth || scanY < 0 || scanY >= (int)fieldHeight)
								continue;

							revealSpot(scanX, scanY);
						}
				}
		}

		return false;
	}
	Field(uint numberOfMines, uint fieldWidth, uint fieldHeight, int zeroAdjacentMinesLocationX = -1, int zeroAdjacentMinesLocationY = -1)
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
			firstSpotZero = true;

		if(numberOfMines > fieldHeight * fieldWidth - 9 * (int)firstSpotZero)
			this->numberOfMines = fieldWidth * fieldHeight - 9 * (int)firstSpotZero;

		if(this->numberOfMines < 0)
			this->numberOfMines = 0;

		for(uint count = 0; count < numberOfMines; ++count)
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

		for(uint x = 0; x < fieldWidth; ++x)
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
			revealSpot(zeroAdjacentMinesLocationX, zeroAdjacentMinesLocationY);
	}
	void markSpot(uint x, uint y)
	{
		if(x >= 0 && x < fieldWidth && y >= 0 && y < fieldHeight)	// not out of bounds
			if(!revealedSpaces[x][y])								// space isn't already revealed
				marked[x][y] = !marked[x][y];						// change whether or not it's marked
	}
	bool clearUnmarkedArea(uint x, uint y)	// returns true if a mine was revealed
	{
		for(int scanX = x - 1; scanX <= (int)x + 1; ++scanX)
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
	friend ostream& operator<<(ostream& os, const Field& field)		// output field
	{
		os << ' ';
		for(uint x = 0; x < field.fieldWidth; ++x)
		{
			if(x % 5 == 0)
				os << verticalDash;
			else
				os << marginSpacer;
		}
		os << endl;
		for(uint y = 0; y < field.fieldHeight; ++y)
		{
			if(y % 5 == 0)
				os << horizontalDash;
			else
				os << marginSpacer;

			for(uint x = 0; x < field.fieldWidth; ++x)
			{
				if(field.revealedSpaces[x][y])
				{
					if(field.mines[x][y])
						os << mineChar;
					else
						os << field.numberOfNearbyMines[x][y];
				}
				else
				{
					if(field.marked[x][y])
						os << markedChar;
					else
						os << hiddenChar;
				}
			}
			os << endl;
		}

		return os;
	}
	int numberOfRevealedSpaces()
	{
		int count = 0;
		for(uint x = 0; x < fieldWidth; ++x)
			for(uint y = 0; y < fieldHeight; ++y)
				if(revealedSpaces[x][y])
					++count;
		return count;
	}
	int numberOfUnrevealedSpaces()
	{
		return (int)fieldHeight * (int)fieldWidth - numberOfRevealedSpaces();
	}

private:
	Field();
};

int main()
{
	uint fieldWidth = defaultFieldWidth, fieldHeight = defaultFieldHeight, numberOfMines = defaultNumberOfMines;
	stringstream ssWidthPrompt, ssHeightPrompt, ssMineNumberPrompt;
	ssWidthPrompt << "Enter field width (default is " << defaultFieldWidth << "): " << endl;
	ssHeightPrompt << "Enter field height (default is " << defaultFieldHeight << "): " << endl;
	ssMineNumberPrompt << "Enter the number of mines (default is " << defaultNumberOfMines << "): " << endl;

	fieldWidth = getUint(ssWidthPrompt.str(), cin, cout);
	fieldHeight = getUint(ssHeightPrompt.str(), cin, cout);
	numberOfMines = getUint(ssMineNumberPrompt.str(), cin, cout);

	Field field(0, fieldWidth, fieldHeight);
	bool firstMove = true, gameOver = false, victory = false;

	while(!gameOver)
	{
		cout << endl << field << endl;

		bool correctInput = false;
		while(!correctInput)
		{
			char command = getChar("Action ([r]eveal, [m]ark, [c]lear): ", cin, cout, false);
			stringstream ssXPrompt, ssYPrompt;
			ssXPrompt << "X Coordinate (0 - " << fieldWidth - 1 << "): ";
			ssYPrompt << "Y Coordinate (0 - " << fieldHeight - 1 << "): ";
			uint x = getUint(ssXPrompt.str(), cin, cout);
			uint y = getUint(ssYPrompt.str(), cin, cout);

			if((command == 'r' || command == 'm' || command == 'c') && (x >= 0 && x < fieldWidth) && (y >= 0 && y < fieldHeight))	// valid input
			{
				correctInput = true;

				if(command == 'r')
				{
					if(firstMove)
					{
						field = Field(numberOfMines, fieldWidth, fieldHeight, x, y);
						firstMove = false;
					}
					else if(field.revealSpot(x, y))
					{
						gameOver = true;
						victory = false;
					}
					else if(field.numberOfUnrevealedSpaces() == numberOfMines)
					{
						gameOver = true;
						victory = true;
					}
				}
				else if(command == 'm')
				{
					field.markSpot(x, y);
				}
				else if(command == 'c')
				{
					if(firstMove)
					{
						field = Field(numberOfMines, fieldWidth, fieldHeight, x, y);
						firstMove = false;
					}
					else if(field.clearUnmarkedArea(x, y))
					{
						gameOver= true;
						victory = false;
					}
					else if(field.numberOfUnrevealedSpaces() == field.numberOfMines)
					{
						gameOver = true;
						victory = true;
					}
				}
			}
		}
	}

	cout << field << endl;
	if(victory)
		cout << "Congratulations, you won!" << endl;
	else
		cout << "Game over! You revealed a mine, try again." << endl;

	system("pause");

	return 0;
}