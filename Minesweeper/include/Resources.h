#pragma once

#include <SFML/Graphics.hpp>

class Resources
{
public:
	sf::Texture background, mine, mark, area, invisibleButton, upButton, downButton;
	sf::Font timesFont, squareFont;

	~Resources();

	void loadResources();
	void setSmooth(bool isSmooth);

	static Resources& getInstance();
	
private:
	Resources();  

	Resources(Resources const&);		// do not implement
	void operator=(Resources const&);	// do not implement
};

