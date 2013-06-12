#include "GameState.h"

#include <SFML/System.hpp>

#include "MinesweeperApp.h"
#include "Resources.h"
#include "Settings.h"

GameState::GameState()
	: field(0, 1, 1)
{
	leftButtonDown = false;
	rightButtonDown = false;
	middleButtonDown = false;
	firstMove = true;
	inputReady = false;
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

	app.window.draw(field);

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
}
void GameState::updateButtons(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMiddleDown)
{
	field.updateFieldClicks(mousePosition, isLeftDown, isRightDown, isMiddleDown);
}
void GameState::newGame()
{
	firstMove = true;
	field = Field(Settings::getNumberOfMines(), 
		Settings::getFieldWidth(), 
		Settings::getFieldHeight());

	MinesweeperApp& app = MinesweeperApp::getInstance();
	if(app.currentState == &app.gameState)
	{
		sf::View view;
		view.setSize((float)field.fieldWidth * Resources::getInstance().area.getSize().y,
			(float)field.fieldHeight * Resources::getInstance().area.getSize().y);
		view.setCenter((float)field.fieldWidth * Resources::getInstance().area.getSize().y * 0.5f,
			(float)field.fieldHeight * Resources::getInstance().area.getSize().y * 0.5f);
		app.window.setView(view);
	}
		
}
void GameState::back()
{

}
