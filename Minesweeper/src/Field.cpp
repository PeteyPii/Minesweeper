#include "Field.h"

#include <cmath>

#include "ClickableButton.h"
#include "Globals.h"
#include "MinesweeperApp.h"
#include "Resources.h"

using namespace std;

// definitions of static constants
const unsigned char Field::mineChar = 15;		
const unsigned char Field::markedChar = 4;
const unsigned char Field::hiddenChar = 35;
const unsigned char Field::verticalDash = 186;
const unsigned char Field::horizontalDash = 205;
const unsigned char Field::marginSpacer = 249;
const sf::Color Field::backgroundColour = sf::Color(225, 225, 225, 255);
const sf::Color Field::numberColours[] = {sf::Color(0, 0, 0, 0),	// 0
	sf::Color(100, 100, 255, 255),	// 1
	sf::Color(0, 192, 0, 255),		// 2
	sf::Color(255, 40, 40, 255),	// 3
	sf::Color(0, 0, 255, 255),		// 4				
	sf::Color(128, 0, 128, 255),	// 5
	sf::Color(0, 128, 128, 255),	// 6
	sf::Color(128, 128, 255, 255),	// 7
	sf::Color(128, 128, 128, 255),	// 8
	sf::Color(0, 0, 0, 0)};			// 9
const sf::Color Field::hoverColour = sf::Color(255, 255, 255, 78);
const sf::Color Field::clickedColour = sf::Color(0, 0, 0, 60);
const float Field::nearbyMineNumberTextSizeFactor = 0.7f;

Field::Field(uint numberOfMines, uint fieldWidth, uint fieldHeight, bool firstMoveZero)
	: mines(fieldWidth, vector<bool>(fieldHeight, false)),
	revealed(fieldWidth, vector<bool>(fieldHeight, false)),
	marked(fieldWidth, vector<bool>(fieldHeight, false)),
	numberOfNearbyMines(fieldWidth, vector<int>(fieldHeight, 0)),
	buttonsLMB(fieldWidth, vector<ClickableButton>(fieldHeight, ClickableButton())),
	buttonsRMB(fieldWidth, vector<ClickableButton>(fieldHeight, ClickableButton())),
	buttonsMMB(fieldWidth, vector<ClickableButton>(fieldHeight, ClickableButton())),
	buttonsVisual(fieldWidth, vector<ClickableButton>(fieldHeight, ClickableButton())),
	textNumbers(fieldWidth, vector<sf::Text>(fieldHeight, sf::Text())),
	numberOfMines(numberOfMines),
	fieldWidth(fieldWidth),
	fieldHeight(fieldHeight)
{
	firstMove = firstMoveZero;

	if(numberOfMines > fieldHeight * fieldWidth - 9 * (int)firstMove)
		this->numberOfMines = fieldWidth * fieldHeight - 9 * (int)firstMove;	// reduce the number of mines to a maximum base don the field

	if(this->numberOfMines < 0)
		this->numberOfMines = 0;	// blanket check to make sure the number of mines is not negative from the previous call

	if(!firstMove)
		generateField();

	MinesweeperApp& app = MinesweeperApp::getInstance();
	Resources& resources = Resources::getInstance();
	uint areaSideLength = resources.area.getSize().y;
	sf::Vector2f buttonSize((float)areaSideLength, (float)areaSideLength);

	for(uint x = 0; x < fieldWidth; ++x)	// set up the buttons on every square
		for(uint y = 0; y < fieldHeight; ++y)
		{
			sf::Vector2f buttonPosition((float)x * areaSideLength, (float)y * areaSideLength);
			
			buttonsVisual[x][y] = ClickableButton(&resources.area, buttonPosition, buttonSize);
			buttonsLMB[x][y] = ClickableButton(&resources.invisibleButton, buttonPosition, buttonSize);
			buttonsRMB[x][y] = ClickableButton(&resources.invisibleButton, buttonPosition, buttonSize);
			buttonsMMB[x][y] = ClickableButton(&resources.invisibleButton, buttonPosition, buttonSize);

			sf::Uint8 colour = (sf::Uint8)(255.0f * (0.6f + 0.4f * sqrt((float)(x * areaSideLength + y * areaSideLength)) / sqrt((float)(fieldWidth * areaSideLength + fieldHeight * areaSideLength + 2 * areaSideLength))));
			buttonsVisual[x][y].sprite.setColor(sf::Color(colour, colour, colour, 255));
		}

	background = sf::RectangleShape(sf::Vector2f((float)fieldWidth * areaSideLength, (float)fieldHeight * areaSideLength));
	background.setFillColor(backgroundColour);
	background.setOutlineThickness(0.0f);

	hover = sf::RectangleShape(sf::Vector2f((float)areaSideLength, (float)areaSideLength));
	hover.setFillColor(hoverColour);
	hover.setOutlineThickness(0.0f);
	hover.setPosition(-100.0f * areaSideLength, -100.0f * areaSideLength);
}
Field::~Field()
{

}
bool Field::revealSpot(int x, int y)
{
	if(firstMove)
	{
		generateField(x, y);
		firstMove = false;
	}

	if(!revealed[(uint)x][(uint)y] && !marked[x][y])	// the space is not marked or already revealed
	{
		revealed[(uint)x][(uint)y] = true;

		if(mines[(uint)x][(uint)y])	
		{
			return true; // return true because a mine was revealed
		}
		else if(numberOfNearbyMines[(uint)x][(uint)y] == 0)	// recursive check to reveal spaces around a spot with zero nearby mines
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
void Field::markSpot(uint x, uint y)
{
	if(x >= 0 && x < fieldWidth && y >= 0 && y < fieldHeight)	// not out of bounds
		if(!revealed[x][y])								// space isn't already revealed
			marked[x][y] = !marked[x][y];						// change whether or not it's marked
}
bool Field::clearUnmarkedArea(uint x, uint y)	// returns true if a mine was revealed
{
	uint count = 0;
	for(int scanX = x - 1; scanX <= (int)x + 1; ++scanX)
		for(int scanY = y - 1; scanY <= (int)y + 1; ++scanY)
		{
			if(scanX < 0 || scanX >= (int)fieldWidth || scanY < 0 || scanY >= (int)fieldHeight)
				continue;

			if(marked[scanX][scanY])
				++count;
		}

	if(revealed[x][y] && count == numberOfNearbyMines[x][y])
	{
		bool returnValue = false;
		for(int scanX = x - 1; scanX <= (int)x + 1; ++scanX)	// go through the 3x3 area around a location and reveal unmarked squares
			for(int scanY = y - 1; scanY <= (int)y + 1; ++scanY)
			{
				if(scanX < 0 || scanX >= (int)fieldWidth || scanY < 0 || scanY >= (int)fieldHeight)
					continue;

				if(!revealed[(uint)scanX][(uint)scanY] && !marked[(uint)scanX][(uint)scanY])
					if(revealSpot(scanX, scanY))
						returnValue = true;
			}

			return returnValue;
	}
	else
	{
		return false;
	}
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
			if(field.revealed[x][y])
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
			if(revealed[x][y])
				++count;
	return count;
}
int Field::numberOfUnrevealedSpaces()
{
	// number of unrevealed spaces is the field area minus the number of revealed spaces
	return (int)fieldHeight * (int)fieldWidth - numberOfRevealedSpaces();
}
uint Field::numberOfDetectedMines()
{
	// go through the field and check if a location has a mine
	uint count = 0;
	for(uint x = 0; x < fieldWidth; ++x)
		for(uint y = 0; y < fieldHeight; ++y)
			if(marked[x][y])
				++count;
	return count;
}
int Field::numberOfUndetectedMines()
{
	return (int)(numberOfMines - numberOfDetectedMines());
}
void Field::draw(sf::RenderTarget& target, sf::RenderStates renderStates) const
{
	target.draw(background);
	uint areaSideLength = Resources::getInstance().area.getSize().y;

	sf::Sprite mine(Resources::getInstance().mine);
	sf::Sprite mark(Resources::getInstance().mark);

	for(uint x = 0; x < fieldWidth; ++x)
		for(uint y = 0; y < fieldHeight; ++y)
		{
			if(revealed[x][y])
			{
				if(mines[x][y])
				{
					mine.setPosition((float)x * areaSideLength + position.x, (float)y * areaSideLength + position.y);
					target.draw(mine);
				}
				else
				{
					target.draw(textNumbers[x][y]);
				}
			}
			else
			{
				target.draw(buttonsVisual[x][y]);
				if(marked[x][y])
				{
					
					mark.setPosition((float)x * areaSideLength + position.x, (float)y * areaSideLength + position.y);
					target.draw(mark);
				}
			}

			sf::FloatRect rect((float)x * areaSideLength + position.x, (float)y * areaSideLength + position.y, (float)areaSideLength, (float)areaSideLength);
			drawRectangle(target, rect, sf::Color::White);
		}

	if(hover.getPosition().x >= position.x && hover.getPosition().x < position.x + fieldWidth * areaSideLength && 
		hover.getPosition().y >= position.y && hover.getPosition().y < position.y + fieldHeight * areaSideLength)
		target.draw(hover);
}
void Field::updateFieldClicks(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMiddleDown)
{
	if(isLeftDown || isRightDown || isMiddleDown)
		hover.setFillColor(clickedColour);
	else
		hover.setFillColor(hoverColour);
	float rX = fmod(position.x, hover.getSize().x);
	float rY = fmod(position.y, hover.getSize().y);
	hover.setPosition((float)((uint)(mousePosition.x - position.x) / (uint)hover.getSize().x * (uint)hover.getSize().x) + position.x, 
		(float)((uint)(mousePosition.y - position.y) / (uint)hover.getSize().y * (uint)hover.getSize().y) + position.y);

	for(uint x = 0; x < fieldWidth; ++x)
		for(uint y = 0; y < fieldHeight; ++y)
		{
			Clickable::ClickType returnLMB =  buttonsLMB[x][y].updateAndGetClicked(mousePosition, isLeftDown);
			if(returnLMB == Clickable::CLICKED)	// left click to reveal squares
				revealSpot((int)x, (int)y);
			else if(returnLMB == Clickable::DOUBLE_CLICKED)	// double click to clear around a square
				clearUnmarkedArea(x, y);

			if(buttonsRMB[x][y].updateAndGetClicked(mousePosition, isRightDown))	// right click to mark squares
				markSpot(x, y);

			if(buttonsMMB[x][y].updateAndGetClicked(mousePosition, isMiddleDown || (isRightDown && isLeftDown)))	// middle click or both left and right click to clear around a square
				clearUnmarkedArea(x, y);

			buttonsVisual[x][y].updateAndGetClicked(mousePosition, isLeftDown || isRightDown || isMiddleDown);	// call to draw the square properly
		}
}
void Field::generateField(int zeroAdjacentMinesLocationX, int zeroAdjacentMinesLocationY)
{
	for(uint count = 0; count < numberOfMines; ++count)	// loop that places all the mines in random positions except where the first reveal is (if it is set)
	{
		bool minePlaced = false;
		while(!minePlaced)
		{
			int randX = random() % fieldWidth;
			int randY = random() % fieldHeight;

			if(!mines[(uint)randX][(uint)randY])
			{
				if(firstMove)
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

	for(uint x = 0; x < fieldWidth; ++x)	// calculate the number of nearby mines for every nearby square
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

	Resources& resources = Resources::getInstance();
	uint areaSideLength = resources.area.getSize().y;

	for(uint x = 0; x < fieldWidth; ++x)	// set up the nearby mine number text for every square
		for(uint y = 0; y < fieldHeight; ++y)
		{
			textNumbers[x][y] = sf::Text(numberToString(numberOfNearbyMines[x][y]), resources.squareFont, (uint)(nearbyMineNumberTextSizeFactor * areaSideLength));
			textNumbers[x][y].setPosition((x + 0.5f) * areaSideLength - 0.025f * areaSideLength + position.x, (y + 0.5f) * areaSideLength - 0.18f * areaSideLength + position.y);
			textNumbers[x][y].setColor(numberColours[numberOfNearbyMines[x][y]]);
			centerOrigin(textNumbers[x][y]);
		}
}
bool Field::isVictoryReached()
{
	return numberOfUnrevealedSpaces() == numberOfMines && !isDefeatReached();
}
bool Field::isDefeatReached()
{
	for(uint x = 0; x < fieldWidth; ++x)	// go through entire field and see if a mine was revealed
		for(uint y = 0; y < fieldHeight; ++y)
		{
			if(revealed[x][y] && mines[x][y])
				return true;
		}

	return false;
}
void Field::setFieldPosition(sf::Vector2f position)
{
	this->position = position;
	Resources& resources = Resources::getInstance();
	uint areaSideLength = resources.area.getSize().y;

	background.setPosition(position);

	for(uint x = 0; x < fieldWidth; ++x)	// set the position for all the squares and all the text digits
		for(uint y = 0; y < fieldHeight; ++y)
		{
			buttonsVisual[x][y].setPosition((float)x * areaSideLength + position.x, (float)y * areaSideLength + position.y);
			buttonsLMB[x][y].setPosition((float)x * areaSideLength + position.x, (float)y * areaSideLength + position.y);
			buttonsRMB[x][y].setPosition((float)x * areaSideLength + position.x, (float)y * areaSideLength + position.y);
			buttonsMMB[x][y].setPosition((float)x * areaSideLength + position.x, (float)y * areaSideLength + position.y);
			textNumbers[x][y].setPosition((x + 0.5f) * areaSideLength + position.x, (y + 0.5f) * areaSideLength - 3 + position.y);
			centerOrigin(textNumbers[x][y]);
		}
}
void Field::setFieldPosition(float positionX, float positionY)
{
	setFieldPosition(sf::Vector2f(positionX, positionY));
}
