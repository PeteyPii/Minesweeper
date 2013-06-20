#include "GameState.h"

#include <sstream>

#include "Globals.h"
#include "MinesweeperApp.h"
#include "Resources.h"
#include "Settings.h"

using namespace std;

const float GameState::infoTextSizeFactor = 0.5f;
const float GameState::gameOverTextFactor = 0.1f;
const float GameState::statsTextSizeFactor = 0.05f;

GameState::GameState()
	: field(0, 1, 1)
{
	leftButtonDown = false;
	rightButtonDown = false;
	middleButtonDown = false;
	inputReady = false;
	windowFocused = true;

	Resources& resources = Resources::getInstance();

	background = sf::Sprite(resources.background);
	timeElapsedText = sf::Text("", resources.squareFont, 0);
	minesLeft = sf::Text("", resources.squareFont, 0);
	timeElapsedTitle = sf::Text("T: ", resources.squareFont, 0);
	timeElapsedTitle.setColor(sf::Color(170, 170, 170, 255));
	minesLeftTitle = sf::Text("M: ", resources.squareFont, 0);
	minesLeftTitle.setColor(sf::Color(170, 170, 170, 255));
	playAgainText = sf::Text("Press R to play again", resources.squareFont, 0);
	victoryText = sf::Text("You won!", resources.squareFont, 0);
	defeatText = sf::Text("You lost...", resources.squareFont, 0);
	backgroundShade.setFillColor(sf::Color(0, 0, 0, 128));
}
GameState::~GameState()
{

}
void GameState::step()
{
	if(!inputReady)
		inputReady = true;

	if(gameBegan && !isVictory && !isDefeat && windowFocused)
	{
		timeElapsed += clock.restart();
		timeElapsedText.setString(numberToString(timeElapsed.asSeconds()));
	}
	else
	{
		clock.restart();
	}
}
void GameState::draw()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();

	app.window.clear(sf::Color::White);

	app.window.draw(background);
	if(windowFocused || isVictory || isDefeat)
		app.window.draw(field);
	app.window.draw(timeElapsedTitle);
	app.window.draw(timeElapsedText);
	app.window.draw(minesLeftTitle);
	app.window.draw(minesLeft);

	if(isDefeat || isVictory)
	{
		app.window.draw(backgroundShade);

		if(isDefeat)
			app.window.draw(defeatText);
		else if(isVictory)
			app.window.draw(victoryText);

		app.window.draw(lastTimeText);
		app.window.draw(playAgainText);
		app.window.draw(numberOfWinsText);
		app.window.draw(numberOfGamesText);
		app.window.draw(winPercentageText);
		app.window.draw(bestTimeText);
		app.window.draw(averageTimeText);
	}

	if(!windowFocused && !isDefeat && !isVictory)
		app.window.draw(backgroundShade);

	app.window.display();
}
void GameState::eventMouseMoved(sf::Event mouseEvent)
{
	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseMove.x, mouseEvent.mouseMove.y)), leftButtonDown, rightButtonDown, middleButtonDown);
}
void GameState::eventMouseButtonPressed(sf::Event mouseEvent)
{
	if(inputReady && !isVictory && !isDefeat)
	{
		if(mouseEvent.mouseButton.button == sf::Mouse::Left)
			leftButtonDown = true;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Right)
			rightButtonDown = true;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Middle)
			middleButtonDown = true;

		updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown, rightButtonDown, middleButtonDown);
		minesLeft.setString(numberToString(field.numberOfUndetectedMines()));

		if(field.numberOfRevealedSpaces() != 0 && !gameBegan)
		{
			clock.restart();
			gameBegan = true;
			Settings::setNumberOfFieldGames(field.fieldWidth, field.fieldHeight, field.numberOfMines, Settings::getNumberOfFieldGames(field.fieldWidth, field.fieldHeight, field.numberOfMines) + 1);
		}

		if(field.isDefeatReached())
		{
			isDefeat = true;
			updateStatsTexts();
		}
		else if(field.isVictoryReached())
		{
			isVictory = true;
			
			Settings::setNumberOfFieldWins(field.fieldWidth, field.fieldHeight, field.numberOfMines, Settings::getNumberOfFieldWins(field.fieldWidth, field.fieldHeight, field.numberOfMines) + 1);
			Settings::setTotalFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines, Settings::getTotalFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines) + timeElapsed.asSeconds());
			Settings::setBestFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines, std::min(Settings::getBestFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines), timeElapsed.asSeconds()));

			updateStatsTexts();
		}
	}
}
void GameState::eventMouseButtonReleased(sf::Event mouseEvent)
{
	if(inputReady && !isVictory && !isDefeat)
	{
		if(mouseEvent.mouseButton.button == sf::Mouse::Left)
			leftButtonDown = false;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Right)
			rightButtonDown = false;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Middle)
			middleButtonDown = false;

		updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown, rightButtonDown, middleButtonDown);
		minesLeft.setString(numberToString(field.numberOfUndetectedMines()));

		if(field.numberOfRevealedSpaces() != 0 && !gameBegan)
		{
			clock = sf::Clock();
			gameBegan = true;
			Settings::setNumberOfFieldGames(field.fieldWidth, field.fieldHeight, field.numberOfMines, Settings::getNumberOfFieldGames(field.fieldWidth, field.fieldHeight, field.numberOfMines) + 1);
		}

		if(field.isDefeatReached())
		{
			isDefeat = true;
			updateStatsTexts();
		}
		else if(field.isVictoryReached())
		{
			isVictory = true;

			Settings::setNumberOfFieldWins(field.fieldWidth, field.fieldHeight, field.numberOfMines, Settings::getNumberOfFieldWins(field.fieldWidth, field.fieldHeight, field.numberOfMines) + 1);
			Settings::setTotalFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines, Settings::getTotalFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines) + timeElapsed.asSeconds());
			Settings::setBestFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines, std::min(Settings::getBestFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines), timeElapsed.asSeconds()));

			updateStatsTexts();
		}
	}
}
void GameState::eventKeyPressed(sf::Event keyEvent)
{
	if(keyEvent.key.code == sf::Keyboard::Escape)
		back();
	else if(keyEvent.key.code == sf::Keyboard::R)
	{
		if(gameBegan && !isVictory && !isDefeat)
			Settings::setNumberOfFieldGames(field.fieldWidth, field.fieldHeight, field.numberOfMines, Settings::getNumberOfFieldGames(field.fieldWidth, field.fieldHeight, field.numberOfMines) + 1);
		newGame();
	}
}
void GameState::eventMouseExited()
{
	updateButtons(sf::Vector2f(-1.0f, -1.0f), leftButtonDown, rightButtonDown, middleButtonDown);
}
void GameState::eventWindowUnfocused()
{
	windowFocused = false;
}
void GameState::eventWindowFocused()
{
	windowFocused = true;
}
void GameState::updateButtons(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMiddleDown)
{
	field.updateFieldClicks(mousePosition, isLeftDown, isRightDown, isMiddleDown);
}
void GameState::updateStatsTexts()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();
	Resources& resources = Resources::getInstance();

	stringstream timeText, winsText, gamesText, percentText, bestText, averageText;
	uint numberOfWins = Settings::getNumberOfFieldWins(field.fieldWidth, field.fieldHeight, field.numberOfMines);
	uint numberOfGames = Settings::getNumberOfFieldGames(field.fieldWidth, field.fieldHeight, field.numberOfMines);

	timeText << "Game time: " << numberToString(timeElapsed.asSeconds());
	winsText << "Games won: " << numberOfWins;
	gamesText << "Number of games: " << numberOfGames;

	if(numberOfGames > 0)
		percentText << "Win percentage: " << numberToString((float)numberOfWins / (float)numberOfGames * 100.0f) << " %";
	else
		percentText << "Win percentage: N/A";

	if(numberOfWins > 0)
	{
		bestText << "Best time: " << Settings::getBestFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines);
		averageText << "Average time: " << numberToString(Settings::getTotalFieldTime(field.fieldWidth, field.fieldHeight, field.numberOfMines) / numberOfWins);
	}
	else
	{
		bestText << "Best time: N/A";
		averageText << "Average time: N/A";
	}

	const sf::View& view = app.window.getView();
	uint characterSize = (uint)(std::min(view.getSize().x, view.getSize().y) * statsTextSizeFactor);

	lastTimeText = sf::Text(timeText.str(), resources.squareFont, characterSize);
	lastTimeText.setPosition(0.025f * view.getSize().x, 0.675f * view.getSize().y);
	numberOfWinsText = sf::Text(winsText.str(), resources.squareFont, characterSize);
	numberOfWinsText.setPosition(0.025f * view.getSize().x, 0.725f * view.getSize().y);
	numberOfGamesText = sf::Text(gamesText.str(), resources.squareFont, characterSize);
	numberOfGamesText.setPosition(0.025f * view.getSize().x, 0.775f * view.getSize().y);
	winPercentageText = sf::Text(percentText.str(), resources.squareFont, characterSize);
	winPercentageText.setPosition(0.025f * view.getSize().x, 0.825f * view.getSize().y);
	bestTimeText = sf::Text(bestText.str(), resources.squareFont, characterSize);
	bestTimeText.setPosition(0.025f * view.getSize().x, 0.875f * view.getSize().y);
	averageTimeText = sf::Text(averageText.str(), resources.squareFont, characterSize);
	averageTimeText.setPosition(0.025f * view.getSize().x, 0.925f * view.getSize().y);
}
void GameState::newGame()
{
	gameBegan = false;
	isVictory = false;
	isDefeat = false;
	timeElapsed = timeElapsed.Zero;
	field = Field(Settings::getNumberOfMines(), 
		Settings::getFieldWidth(), 
		Settings::getFieldHeight(),
		true);
	field.setFieldPosition((float)fieldMargin, (float)fieldMargin);

	MinesweeperApp& app = MinesweeperApp::getInstance();
	if(app.currentState == &app.gameState)
	{
		sf::View view;
		view.setSize((float)field.fieldWidth * Resources::getInstance().area.getSize().y + 2 * fieldMargin,
			(float)field.fieldHeight * Resources::getInstance().area.getSize().y + 2 * fieldMargin);
		view.setCenter(view.getSize().x * 0.5f,
			view.getSize().y * 0.5f);
		app.window.setView(view);

		background.setScale(view.getSize().x / background.getTexture()->getSize().x, 
			view.getSize().y / background.getTexture()->getSize().y);
		
		timeElapsedTitle.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
		timeElapsedTitle.setPosition(view.getSize().x * 0.275f, view.getSize().y - fieldMargin * 0.6f);
		centerOrigin(timeElapsedTitle);

		timeElapsedText.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
		timeElapsedText.setString("0");
		centerOrigin(timeElapsedText);
		timeElapsedText.setPosition(timeElapsedTitle.getGlobalBounds().left + timeElapsedTitle.getGlobalBounds().width + 10.0f, 
			view.getSize().y - fieldMargin * 0.6f);

		minesLeftTitle.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
		minesLeftTitle.setPosition(view.getSize().x * 0.625f, view.getSize().y - fieldMargin * 0.6f);
		centerOrigin(minesLeftTitle);

		minesLeft.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
		minesLeft.setString("0");		// for the origin
		centerOrigin(minesLeft);
		minesLeft.setString(numberToString(field.numberOfUndetectedMines()));
		minesLeft.setPosition(minesLeftTitle.getGlobalBounds().left + minesLeftTitle.getGlobalBounds().width + 10.0f, 
			view.getSize().y - fieldMargin * 0.6f);

		playAgainText.setCharacterSize((uint)(std::min(view.getSize().x, view.getSize().y) * gameOverTextFactor * 0.5f));
		playAgainText.setPosition(view.getSize().x * 0.5f, view.getSize().y * 0.4f);
		centerOrigin(playAgainText);
		
		victoryText.setCharacterSize((uint)(std::min(view.getSize().x, view.getSize().y) * gameOverTextFactor));
		victoryText.setPosition(view.getSize().x * 0.5f, view.getSize().y * 0.2f);
		centerOrigin(victoryText);

		defeatText.setCharacterSize((uint)(std::min(view.getSize().x, view.getSize().y) * gameOverTextFactor));
		defeatText.setPosition(view.getSize().x * 0.5f, view.getSize().y * 0.2f);
		centerOrigin(defeatText);

		backgroundShade.setSize(view.getSize());
	}	
}
void GameState::back()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();
	app.window.setView(app.window.getDefaultView());
	app.currentState = &app.mainMenuState;
}
