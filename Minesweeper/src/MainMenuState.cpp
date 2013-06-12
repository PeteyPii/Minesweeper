#include "MainMenuState.h"

#include <SFML/System.hpp>

#include "Globals.h"
#include "MinesweeperApp.h"
#include "Resources.h"

MainMenuState::MainMenuState()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();
	Resources& resources = Resources::getInstance();

	background = sf::Sprite(resources.background);
	background.setScale((float)app.window.getSize().x / background.getTexture()->getSize().x, (float)app.window.getSize().y / background.getTexture()->getSize().y);

	title = sf::Text("Minesweeper", resources.timesFont, app.window.getSize().x / 9);
	title.setPosition(0.5f * app.window.getSize().x, 0.2f * app.window.getSize().y);
	centerOrigin(title);

	playGame = ClickableText("Play", 
		sf::Vector2f(0.5f * app.window.getSize().x, 0.6f * app.window.getSize().y), 
		app.window.getSize().x / 15, 
		&resources.timesFont);
	centerOrigin(playGame.text);
	playGame.updateBoundingBox();

	exitGame = ClickableText("Exit", 
		sf::Vector2f(0.5f * app.window.getSize().x, 0.7f * app.window.getSize().y), 
		app.window.getSize().x / 15, 
		&resources.timesFont);
	centerOrigin(exitGame.text);
	exitGame.updateBoundingBox();

	leftButtonDown = false;
}
MainMenuState::~MainMenuState()
{

}
void MainMenuState::step()
{
	
}
void MainMenuState::draw()
{
	MinesweeperApp& app = MinesweeperApp::getInstance();

	app.window.draw(background);
	app.window.draw(title);
	app.window.draw(playGame);
	app.window.draw(exitGame);

	app.window.display();
}
void MainMenuState::eventMouseMoved(sf::Event mouseEvent)
{
	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseMove.x, mouseEvent.mouseMove.y)), leftButtonDown);
}
void MainMenuState::eventMouseButtonPressed(sf::Event mouseEvent)
{
	if(mouseEvent.mouseButton.button == sf::Mouse::Left)
		leftButtonDown = true;

	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown);
}
void MainMenuState::eventMouseButtonReleased(sf::Event mouseEvent)
{
	if(mouseEvent.mouseButton.button == sf::Mouse::Left)
		leftButtonDown = false;

	updateButtons(MinesweeperApp::getInstance().window.mapPixelToCoords(sf::Vector2i(mouseEvent.mouseButton.x, mouseEvent.mouseButton.y)), leftButtonDown);
}
void MainMenuState::eventKeyPressed(sf::Event keyEvent)
{
	if(keyEvent.key.code == sf::Keyboard::Escape)
		exit();
}
void MainMenuState::updateButtons(sf::Vector2f mousePosition, bool isLeftDown)
{
	if(playGame.updateAndGetClicked(mousePosition, isLeftDown))
		play();

	if(exitGame.updateAndGetClicked(mousePosition, isLeftDown))
		exit();
}
void MainMenuState::play()
{
	playGame.resetStates();
}
void MainMenuState::exit()
{
	MinesweeperApp::getInstance().stop();
}


