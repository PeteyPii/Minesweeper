#include <ctime>
#include <iostream>
#include <vector>

#include "mtrand.h"

MTRand_int32 random((unsigned long)time(0));

using namespace std;
typedef unsigned int uint;											// typedef for faster typing
const char mineChar = 15, markedChar = 33, hiddenChar = 176;		// constant characters for outputting special squares

class Field
{
public:
	vector<vector<bool> > mines;			// true for a mine in the spot
	vector<vector<bool> > revealedSpaces;	// true for a revealed square
	vector<vector<bool> > marked;			// true for a space marked as a present mine
	vector<vector<int> > numberOfNearbyMines;

	int numberOfMines;
	uint fieldWidth, fieldHeight;

	bool revealSpot(int locX, int locY)	// returns true when a mine is hit
	{
		if(!revealedSpaces[(uint)locX][(uint)locY])
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
	}
	Field(int numberOfMines, uint fieldWidth, uint fieldHeight, int zeroAdjacentMinesLocationX = -1, int zeroAdjacentMinesLocationY = -1)
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

		for(int count = 0; count <= numberOfMines; ++count)
		{
			bool minePlaced = false;
			while(!minePlaced)
			{
				int randX = random() % fieldWidth;
				int randY = random() % fieldHeight;

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
	friend ostream& operator<<(ostream& os, const Field& field)
	{
		for(uint y = 0; y < field.fieldHeight; ++y)
		{
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
			cout << endl;
		}

		return os;
	}

private:
	Field();
};

int main()
{
	Field field(99, 30, 16, 15, 8);
	cout << field << endl;

	system("pause");

	return 0;
}