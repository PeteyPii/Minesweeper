#pragma once

#include <SFML/Graphics.hpp>

class Resources
{
public:
	sf::Texture background;
	sf::Font timesFont;

	~Resources();

	void loadResources();

	static Resources& getInstance();
	
private:
	Resources();  

	Resources(Resources const&);	// do not implement
	void operator=(Resources const&);		// do not implement
};

