#include "GameState.h"

#include <SFML/System.hpp>

#include "Globals.h"
#include "MinesweeperApp.h"
#include "Resources.h"
#include "Settings.h"

const float GameState::infoTextSizeFactor = 0.5f;

GameState::GameState()
	: field(0, 1, 1)
{
	leftButtonDown = false;
	rightButtonDown = false;
	middleButtonDown = false;
	inputReady = false;

	Resources& resources = Resources::getInstance();

	background = sf::Sprite(resources.background);
	timeElapsedText = sf::Text("0", resources.squareFont, 0);
	minesLeft = sf::Text("0", resources.squareFont, 0);
	timeElapsedTitle = sf::Text("Time: ", resources.timesFont, 0);
	minesLeftTitle = sf::Text("Mines Left: ", resources.timesFont, 0);
}
GameState::~GameState()
{

}
void GameState::step()
{
	if(!inputReady)
		inputReady = true;
}
void GameState::draw()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();

	app.window.clear(sf::Color::White);

	app.window.draw(background);
	app.window.draw(field);
	app.window.draw(timeElapsedTitle);
	app.window.draw(timeElapsedText);

	app.window.display();
}
void GameState::eventMouseMoved(sf::Event mouseEvent)
{
	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseMove.x, mouseEvent.mouseMove.y)), leftButtonDown, rightButtonDown, middleButtonDown);
}
void GameState::eventMouseButtonPressed(sf::Event mouseEvent)
{
	if(inputReady)
	{
		if(mouseEvent.mouseButton.button == sf::Mouse::Left)
			leftButtonDown = true;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Right)
			rightButtonDown = true;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Middle)
			middleButtonDown = true;

		updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown, rightButtonDown, middleButtonDown);
	}
}
void GameState::eventMouseButtonReleased(sf::Event mouseEvent)
{
	if(inputReady)
	{
		if(mouseEvent.mouseButton.button == sf::Mouse::Left)
			leftButtonDown = false;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Right)
			rightButtonDown = false;
		else if(mouseEvent.mouseButton.button == sf::Mouse::Middle)
			middleButtonDown = false;

		updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown, rightButtonDown, middleButtonDown);
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

		
		minesLeft.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
		timeElapsedTitle.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
		timeElapsedTitle.setPosition(view.getSize().x * 0.3f, view.getSize().y - fieldMargin * 0.5f);
		centerOrigin(timeElapsedTitle);

		timeElapsedText.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
		timeElapsedText.setPosition(timeElapsedTitle.getGlobalBounds().left + timeElapsedTitle.getGlobalBounds().width + 5.0f, timeElapsedTitle.getGlobalBounds().top);
		minesLeftTitle.setCharacterSize((uint)(fieldMargin * infoTextSizeFactor));
	}
		
}
void GameState::back()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();
	app.window.setView(app.window.getDefaultView());
	app.currentState = &app.mainMenuState;
}
