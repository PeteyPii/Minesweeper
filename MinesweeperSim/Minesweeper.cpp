#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

#include "Field.h"
#include "Globals.h"
#include "StreamInput.h"

using namespace std;
	
const uint defaultFieldWidth = 30,
	defaultFieldHeight = 16,
	defaultNumberOfMines = 99;

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