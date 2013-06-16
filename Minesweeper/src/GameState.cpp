#include "GameState.h"

#include "Globals.h"
#include "MinesweeperApp.h"
#include "Resources.h"
#include "Settings.h"

const float GameState::infoTextSizeFactor = 0.5f;
const float GameState::gameOverTextFactor = 0.1f;

GameState::GameState()
	: field(0, 1, 1)
{
	leftButtonDown = false;
	rightButtonDown = false;
	middleButtonDown = false;
	inputReady = false;

	Resources& resources = Resources::getInstance();

	background = sf::Sprite(resources.background);
	timeElapsedText = sf::Text("", resources.squareFont, 0);
	minesLeft = sf::Text("", resources.squareFont, 0);
	timeElapsedTitle = sf::Text("Time: ", resources.squareFont, 0);
	minesLeftTitle = sf::Text("Mines Left: ", resources.squareFont, 0);
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

	if(gameBegan && !isVictory && !isDefeat)
	{
		timeElapsed += clock.restart();
		timeElapsedText.setString(numberToString(timeElapsed.asSeconds()));
	}
}
void GameState::draw()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();

	app.window.clear(sf::Color::White);

	app.window.draw(background);
	app.window.draw(field);
	app.window.draw(timeElapsedTitle);
	app.window.draw(timeElapsedText);
	app.window.draw(minesLeftTitle);
	app.window.draw(minesLeft);

	if(isDefeat)
	{
		app.window.draw(backgroundShade);
		app.window.draw(defeatText);
		app.window.draw(playAgainText);
	}
	else if(isVictory)
	{
		app.window.draw(backgroundShade);
		app.window.draw(victoryText);
		app.window.draw(playAgainText);
	}

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
		}

		if(field.isDefeatReached())
		{
			isDefeat = true;
		}
		else if(field.isVictoryReached())
		{
			isVictory = true;
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
		}

		if(field.isDefeatReached())
		{
			isDefeat = true;
		}
		else if(field.isVictoryReached())
		{
			isVictory = true;
		}
	}
}
void GameState::eventKeyPressed(sf::Event keyEvent)
{
	if(keyEvent.key.code == sf::Keyboard::Escape)
		back();
	else if(keyEvent.key.code == sf::Keyboard::R)
		newGame();
}
void GameState::updateButtons(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMiddleDown)
{
	field.updateFieldClicks(mousePosition, isLeftDown, isRightDown, isMiddleDown);
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

		playAgainText.setCharacterSize((uint)(min(view.getSize().x, view.getSize().y) * gameOverTextFactor * 0.5f));
		playAgainText.setPosition(view.getSize().x * 0.5f, view.getSize().y * 0.6f);
		centerOrigin(playAgainText);
		
		victoryText.setCharacterSize((uint)(min(view.getSize().x, view.getSize().y) * gameOverTextFactor));
		victoryText.setPosition(view.getSize().x * 0.5f, view.getSize().y * 0.4f);
		centerOrigin(victoryText);

		defeatText.setCharacterSize((uint)(min(view.getSize().x, view.getSize().y) * gameOverTextFactor));
		defeatText.setPosition(view.getSize().x * 0.5f, view.getSize().y * 0.4f);
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
