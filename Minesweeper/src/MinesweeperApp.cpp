#include "MinesweeperApp.h"

#include "MainMenuState.h"
#include "Resources.h"
#include "Settings.h"

MinesweeperApp::MinesweeperApp()
	: window(sf::VideoMode(Settings::getWindowWidth(), Settings::getWindowHeight()), "Minesweeper")
{
	window.setFramerateLimit(60);
	keepRunning = true;
	currentState = &mainMenuState;
}
MinesweeperApp::~MinesweeperApp()
{

}
MinesweeperApp& MinesweeperApp::getInstance()
{
	static MinesweeperApp instance;	// guaranteed to be destroyed
									// instantiated on first use
	return instance;
}
void MinesweeperApp::begin()
{
	while(window.isOpen() && keepRunning)
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::MouseMoved)
			{
				currentState->eventMouseMoved(event);
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				currentState->eventMouseButtonPressed(event);
			}
			else if(event.type == sf::Event::MouseButtonReleased)
			{
				currentState->eventMouseButtonReleased(event);
			}
			else if(event.type == sf::Event::KeyPressed)
			{
				currentState->eventKeyPressed(event);
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				currentState->eventKeyReleased(event);
			}
			else if(event.type == sf::Event::TextEntered)
			{
				currentState->eventTextEntered(event);
			}
			else if(event.type == sf::Event::MouseWheelMoved)
			{
				currentState->eventMouseWheelMoved(event);
			}
			else if(event.type == sf::Event::Resized)
			{
				currentState->eventWindowResized(event);
			}
			else if(event.type == sf::Event::Closed)
			{
				window.close();
				return;
			}
		}

		currentState->step();
		currentState->draw();
	}
}
void MinesweeperApp::stop()
{
	keepRunning = false;
}
