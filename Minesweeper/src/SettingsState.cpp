#include "SettingsState.h"

#include <SFML/System.hpp>
#include <sstream>

#include "Globals.h"
#include "MinesweeperApp.h"
#include "Resources.h"
#include "Settings.h"

using namespace std;

SettingsState::SettingsState()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();
	Resources& resources = Resources::getInstance();

	background = sf::Sprite(resources.background);
	background.setScale((float)app.window.getView().getSize().x / background.getTexture()->getSize().x, (float)app.window.getView().getSize().y / background.getTexture()->getSize().y);

	title = sf::Text("Game settings:", resources.squareFont, app.window.getView().getSize().x / 12);
	title.setPosition(0.025f * app.window.getView().getSize().x, 0.0f * app.window.getView().getSize().y);

	applySettings = ClickableText("Apply settings", 
		sf::Vector2f(0.75f * app.window.getView().getSize().x, 0.95f * app.window.getView().getSize().y), 
		app.window.getView().getSize().x / 24, 
		&resources.squareFont);
	centerOrigin(applySettings.text);
	applySettings.updateBoundingBox();
	
	backToMenu = ClickableText("Back to main menu", 
		sf::Vector2f(0.25f * app.window.getView().getSize().x, 0.95f * app.window.getView().getSize().y), 
		app.window.getView().getSize().x / 24, 
		&resources.squareFont);
	centerOrigin(backToMenu.text);
	backToMenu.updateBoundingBox();

	fieldWidth = Settings::getFieldWidth();
	fieldHeight = Settings::getFieldHeight();
	numberOfMines = Settings::getNumberOfMines();

	fieldWidthTitle = sf::Text("Field width:", resources.squareFont, app.window.getView().getSize().x / 18);
	fieldWidthTitle.setPosition(0.15f * app.window.getView().getSize().x, 0.175f * app.window.getView().getSize().y);
	fieldHeightTitle = sf::Text("Field height:", resources.squareFont, fieldWidthTitle.getCharacterSize());
	fieldHeightTitle.setPosition(fieldWidthTitle.getPosition().x, 0.05f * app.window.getView().getSize().y + fieldWidthTitle.getPosition().y);
	numberOfMinesTitle = sf::Text("Number of mines:", resources.squareFont, fieldWidthTitle.getCharacterSize());
	numberOfMinesTitle.setPosition(fieldWidthTitle.getPosition().x, 0.1f * app.window.getView().getSize().y + fieldWidthTitle.getPosition().y);

	fieldWidthBG.setFillColor(sf::Color(0, 0, 0, 80));
	fieldWidthBG.setOutlineThickness(0.0f);
	fieldWidthBG.setSize(sf::Vector2f(0.15f * app.window.getView().getSize().x, 0.045f * app.window.getView().getSize().y));
	fieldWidthBG.setPosition(sf::Vector2f(0.65f * app.window.getView().getSize().x, 0.0125f * app.window.getView().getSize().y + fieldWidthTitle.getPosition().y));
	fieldHeightBG.setFillColor(fieldWidthBG.getFillColor());
	fieldHeightBG.setOutlineThickness(0.0f);
	fieldHeightBG.setSize(fieldWidthBG.getSize());
	fieldHeightBG.setPosition(sf::Vector2f(fieldWidthBG.getPosition().x, 0.0125f * app.window.getView().getSize().y + fieldHeightTitle.getPosition().y));
	numberOfMinesBG.setFillColor(fieldWidthBG.getFillColor());
	numberOfMinesBG.setOutlineThickness(0.0f);
	numberOfMinesBG.setSize(fieldWidthBG.getSize());
	numberOfMinesBG.setPosition(sf::Vector2f(fieldWidthBG.getPosition().x, 0.0125f * app.window.getView().getSize().y + numberOfMinesTitle.getPosition().y));

	fieldWidthText = sf::Text(numberToString(fieldWidth), resources.squareFont, app.window.getView().getSize().x / 20);
	fieldWidthText.setPosition(sf::Vector2f(0.005f * app.window.getView().getSize().x + fieldWidthBG.getPosition().x, -0.0075f * app.window.getView().getSize().y + fieldWidthBG.getPosition().y));
	fieldHeightText = sf::Text(numberToString(fieldHeight), resources.squareFont, fieldWidthText.getCharacterSize());
	fieldHeightText.setPosition(sf::Vector2f(fieldWidthText.getPosition().x, -0.0075f * app.window.getView().getSize().y + fieldHeightBG.getPosition().y));
	numberOfMinesText = sf::Text(numberToString(numberOfMines), resources.squareFont, fieldWidthText.getCharacterSize());
	numberOfMinesText.setPosition(sf::Vector2f(fieldWidthText.getPosition().x, -0.0075f * app.window.getView().getSize().y + numberOfMinesBG.getPosition().y));

	fieldWidthUpButton = ClickableButton(&resources.upButton,
		sf::Vector2f(fieldWidthBG.getPosition().x + fieldWidthBG.getSize().x,
		fieldWidthBG.getPosition().y),
		sf::Vector2f(0.5f * fieldWidthBG.getSize().y,
		0.5f * fieldWidthBG.getSize().y));
	fieldWidthDownButton = ClickableButton(&resources.downButton,
		sf::Vector2f(fieldWidthBG.getPosition().x + fieldWidthBG.getSize().x,
		fieldWidthBG.getPosition().y + 0.5f * fieldWidthBG.getSize().y),
		sf::Vector2f(0.5f * fieldWidthBG.getSize().y,
		0.5f * fieldWidthBG.getSize().y));
	fieldHeightUpButton = ClickableButton(&resources.upButton,
		sf::Vector2f(fieldHeightBG.getPosition().x + fieldHeightBG.getSize().x,
		fieldHeightBG.getPosition().y),
		sf::Vector2f(0.5f * fieldHeightBG.getSize().y,
		0.5f * fieldHeightBG.getSize().y));
	fieldHeightDownButton = ClickableButton(&resources.downButton,
		sf::Vector2f(fieldHeightBG.getPosition().x + fieldHeightBG.getSize().x,
		fieldHeightBG.getPosition().y + 0.5f * fieldHeightBG.getSize().y),
		sf::Vector2f(0.5f * fieldHeightBG.getSize().y,
		0.5f * fieldHeightBG.getSize().y));
	numberOfMinesUpButton = ClickableButton(&resources.upButton,
		sf::Vector2f(numberOfMinesBG.getPosition().x + numberOfMinesBG.getSize().x,
		numberOfMinesBG.getPosition().y),
		sf::Vector2f(0.5f * numberOfMinesBG.getSize().y,
		0.5f * numberOfMinesBG.getSize().y));
	numberOfMinesDownButton = ClickableButton(&resources.downButton,
		sf::Vector2f(numberOfMinesBG.getPosition().x + numberOfMinesBG.getSize().x,
		numberOfMinesBG.getPosition().y + 0.5f * numberOfMinesBG.getSize().y),
		sf::Vector2f(0.5f * numberOfMinesBG.getSize().y,
		0.5f * numberOfMinesBG.getSize().y));

	currentStatsTitle = sf::Text("Current statistics:", resources.squareFont, app.window.getView().getSize().x / 24);
	currentStatsTitle.setPosition(0.025f * app.window.getView().getSize().x, 0.44f * app.window.getView().getSize().y);

	updateStatsText();

	howToResetAllStatsText = sf::Text("Hold control and shift, and press\nthe R key to reset all statistics.", resources.squareFont, app.window.getView().getSize().x / 24);
	howToResetAllStatsText.setPosition(0.5f * app.window.getView().getSize().x, 0.8125f * app.window.getView().getSize().y);
	centerOrigin(howToResetAllStatsText);

	leftButtonDown = false;
	controlDown = false;
	shiftDown = false;
	RDown = false;
}
SettingsState::~SettingsState()
{

}
void SettingsState::step()
{
	
}
void SettingsState::draw()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();

	app.window.draw(background);

	app.window.draw(title);

	app.window.draw(fieldWidthTitle);
	app.window.draw(fieldHeightTitle);
	app.window.draw(numberOfMinesTitle);

	app.window.draw(fieldWidthBG);
	app.window.draw(fieldHeightBG);
	app.window.draw(numberOfMinesBG);

	app.window.draw(fieldWidthText);
	app.window.draw(fieldHeightText);
	app.window.draw(numberOfMinesText);

	app.window.draw(fieldWidthUpButton);
	app.window.draw(fieldWidthDownButton);
	app.window.draw(fieldHeightUpButton);

	app.window.draw(fieldHeightDownButton);
	app.window.draw(numberOfMinesUpButton);
	app.window.draw(numberOfMinesDownButton);

	app.window.draw(currentStatsTitle);
	app.window.draw(numberOfWinsText);
	app.window.draw(numberOfGamesText);
	app.window.draw(winPercentageText);
	app.window.draw(bestTimeText);
	app.window.draw(averageTimeText);

	app.window.draw(howToResetAllStatsText);
	app.window.draw(applySettings);
	app.window.draw(backToMenu);

	app.window.display();
}
void SettingsState::eventMouseMoved(sf::Event mouseEvent)
{
	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseMove.x, mouseEvent.mouseMove.y)), leftButtonDown);
}
void SettingsState::eventMouseButtonPressed(sf::Event mouseEvent)
{
	if(mouseEvent.mouseButton.button == sf::Mouse::Left)
		leftButtonDown = true;

	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown);
}
void SettingsState::eventMouseButtonReleased(sf::Event mouseEvent)
{
	if(mouseEvent.mouseButton.button == sf::Mouse::Left)
		leftButtonDown = false;

	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown);
}
void SettingsState::eventKeyPressed(sf::Event keyEvent)
{
	if(keyEvent.key.code == sf::Keyboard::Escape)
		back();
	else if(keyEvent.key.code == sf::Keyboard::R)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) && 
			(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
		{
			Settings::resetStatistics();
			updateStatsText();
		}
	}
}
void SettingsState::updateButtons(sf::Vector2f mousePosition, bool isLeftDown)
{
	if(applySettings.updateAndGetClicked(mousePosition, isLeftDown))
		apply();

	if(backToMenu.updateAndGetClicked(mousePosition, isLeftDown))
		back();

	if(fieldWidthUpButton.updateAndGetClicked(mousePosition, isLeftDown))
	{
		if(fieldWidth < maxFieldWidth)
		{
			++fieldWidth;
			fieldWidthText.setString(numberToString(fieldWidth));
		}
	}

	if(fieldWidthDownButton.updateAndGetClicked(mousePosition, isLeftDown))
	{
		if(fieldWidth > minFieldWidth)
		{
			--fieldWidth;
			fieldWidthText.setString(numberToString(fieldWidth));

			if(maxMineToFieldSquareRatio * fieldWidth * fieldHeight < (float)numberOfMines)
			{
				numberOfMines = (uint)(maxMineToFieldSquareRatio * fieldWidth * fieldHeight);
				numberOfMinesText.setString(numberToString(numberOfMines));
			}
		}
	}

	if(fieldHeightUpButton.updateAndGetClicked(mousePosition, isLeftDown))
	{
		if(fieldHeight < maxFieldWidth)
		{
			++fieldHeight;
			fieldHeightText.setString(numberToString(fieldHeight));
		}
	}

	if(fieldHeightDownButton.updateAndGetClicked(mousePosition, isLeftDown))
	{
		if(fieldHeight > minFieldHeight)
		{
			--fieldHeight;
			fieldHeightText.setString(numberToString(fieldHeight));

			if(maxMineToFieldSquareRatio * fieldWidth * fieldHeight < (float)numberOfMines)
			{
				numberOfMines = (uint)(maxMineToFieldSquareRatio * fieldWidth * fieldHeight);
				numberOfMinesText.setString(numberToString(numberOfMines));
			}
		}
	}

	if(numberOfMinesUpButton.updateAndGetClicked(mousePosition, isLeftDown))
	{
		if(maxMineToFieldSquareRatio * fieldWidth * fieldHeight >= (float)(numberOfMines + 1))
		{
			++numberOfMines;
			numberOfMinesText.setString(numberToString(numberOfMines));
		}
	}

	if(numberOfMinesDownButton.updateAndGetClicked(mousePosition, isLeftDown))
	{
		if(numberOfMines > 1)
		{
			--numberOfMines;
			numberOfMinesText.setString(numberToString(numberOfMines));
		}
	}
}
void SettingsState::updateStatsText()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();
	Resources& resources = Resources::getInstance();

	stringstream winsText, gamesText, percentText, bestText, averageText;
	uint numberOfWins = Settings::getNumberOfFieldWins(fieldWidth, fieldHeight, numberOfMines);
	uint numberOfGames = Settings::getNumberOfFieldGames(fieldWidth, fieldHeight, numberOfMines);

	winsText << "Games won: " << numberOfWins;
	gamesText << "Number of games: " << numberOfGames;

	if(numberOfGames > 0)
		percentText << "Win percentage: " << numberToString((float)numberOfWins / (float)numberOfGames * 100.0f) << " %";
	else
		percentText << "Win percentage: N/A";

	if(numberOfWins > 0)
	{
		bestText << "Best time: " << Settings::getBestFieldTime(fieldWidth, fieldHeight, numberOfMines);
		averageText << "Average win time: " << numberToString(Settings::getTotalFieldTime(fieldWidth, fieldHeight, numberOfMines) / numberOfWins);
	}
	else
	{
		bestText << "Best time: N/A";
		averageText << "Average time: N/A";
	}

	uint characterSize = app.window.getView().getSize().x / 24;

	numberOfWinsText = sf::Text(winsText.str(), resources.squareFont, characterSize);
	numberOfWinsText.setPosition(0.05f * app.window.getView().getSize().x, 0.5f * app.window.getView().getSize().y);
	numberOfGamesText = sf::Text(gamesText.str(), resources.squareFont, characterSize);
	numberOfGamesText.setPosition(numberOfWinsText.getPosition().x, 0.54f * app.window.getView().getSize().y);
	winPercentageText = sf::Text(percentText.str(), resources.squareFont, characterSize);
	winPercentageText.setPosition(numberOfWinsText.getPosition().x, 0.58f * app.window.getView().getSize().y);
	bestTimeText = sf::Text(bestText.str(), resources.squareFont, characterSize);
	bestTimeText.setPosition(numberOfWinsText.getPosition().x, 0.62f * app.window.getView().getSize().y);
	averageTimeText = sf::Text(averageText.str(), resources.squareFont, characterSize);
	averageTimeText.setPosition(numberOfWinsText.getPosition().x, 0.66f * app.window.getView().getSize().y);
}
void SettingsState::apply()
{
	Settings::setFieldWidth(fieldWidth);
	Settings::setFieldHeight(fieldHeight);
	Settings::setNumberOfMines(numberOfMines);

	updateStatsText();
}
void SettingsState::back()
{
	backToMenu.resetStates();
	MinesweeperApp& app = MinesweeperApp::getInstance();
	app.currentState = app.mainMenuState.get();
}