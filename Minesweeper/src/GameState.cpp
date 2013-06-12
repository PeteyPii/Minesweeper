#include "GameState.h"

#include <SFML/System.hpp>

#include "Field.h"
#include "MinesweeperApp.h"
#include "Resources.h"
#include "Settings.h"

GameState::GameState()
{
	newGame();

	leftButtonDown = false;
	rightButtonDown = false;
}
GameState::~GameState()
{

}
void GameState::step()
{

}
void GameState::draw()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();

	app.window.display();
}
void GameState::eventMouseMoved(sf::Event mouseEvent)
{
	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseMove.x, mouseEvent.mouseMove.y)), leftButtonDown, rightButtonDown, middleMuttonDown);
}
void GameState::eventMouseButtonPressed(sf::Event mouseEvent)
{
	if(mouseEvent.mouseButton.button == sf::Mouse::Left)
		leftButtonDown = true;
	else if(mouseEvent.mouseButton.button == sf::Mouse::Right)
		rightButtonDown = true;
	else if(mouseEvent.mouseButton.button == sf::Mouse::Middle)
		middleMuttonDown = true;

	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown, rightButtonDown, middleMuttonDown);
}
void GameState::eventMouseButtonReleased(sf::Event mouseEvent)
{
	if(mouseEvent.mouseButton.button == sf::Mouse::Left)
		leftButtonDown = false;
	else if(mouseEvent.mouseButton.button == sf::Mouse::Right)
		rightButtonDown = false;
	else if(mouseEvent.mouseButton.button == sf::Mouse::Middle)
		middleMuttonDown = false;

	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown, rightButtonDown, middleMuttonDown);
}
void GameState::eventKeyPressed(sf::Event keyEvent)
{
	if(keyEvent.key.code == sf::Keyboard::Escape)
		back();
}
void GameState::updateButtons(sf::Vector2f mousePosition, bool isLeftDown, bool isRightDown, bool isMIddleDown)
{
	
}
void GameState::newGame()
{
	firstMove = true;
	field = Field(Settings::getNumberOfMines(), 
		Settings::getFieldWidth(), 
		Settings::getFieldHeight());
}
void GameState::back()
{

}
