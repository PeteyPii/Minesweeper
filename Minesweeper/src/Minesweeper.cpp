#include <iostream>
#include <sstream>
#include <vector>

#include "Resources.h"
#include "Field.h"
#include "Globals.h"
#include "MinesweeperApp.h"
#include "Settings.h"
#include "StreamInput.h"

using namespace std;

int main()
{
	Settings::loadSettings();
	Resources::getInstance().loadResources();

	MinesweeperApp::getInstance().begin();

	return 0;
	
	uint fieldWidth, fieldHeight, numberOfMines;
	fieldWidth = Settings::getFieldWidth();
	fieldHeight = Settings::getFieldHeight();
	numberOfMines = Settings::getNumberOfMines();

	Field field(0, fieldWidth, fieldHeight);
	bool firstMove = true, gameOver = false, victory = false, exitingGame = false;

	while(!gameOver)
	{
		cout << endl << field << endl;

		bool correctInput = false;
		while(!correctInput)
		{
			char command = getChar("Action ([r]eveal, [m]ark, [c]lear, [e]xit): ", cin, cout, false);

			if(command == 'e')	// short circuit to exit game
			{
				gameOver = true;
				exitingGame = true;
				break;
			}

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
	else if(exitingGame)
		cout << "Thanks for playing Minesweeper!" << endl;
	else
		cout << "Game over! You revealed a mine, try again." << endl;

	system("pause");

	return 0;
}