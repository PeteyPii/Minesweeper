#pragma once

#include <SFML/Graphics.hpp>

class ClientResources
{
public:
	sf::Texture background;
	sf::Font timesFont;

	~ClientResources();

	void loadResources();

	static ClientResources& getInstance();
	
private:
	ClientResources();  

	ClientResources(ClientResources const&);	// do not implement
	void operator=(ClientResources const&);		// do not implement
};

