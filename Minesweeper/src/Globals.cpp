#include "Globals.h"

#include <ctime>

using namespace std;

extern MTRand_int32 random((unsigned long)time(0));

void centerOrigin(sf::Text& text)
{
	text.setOrigin(0.5f * text.getLocalBounds().width, 0.5f * text.getLocalBounds().height);
}
void drawRectangle(sf::RenderTarget &target, sf::FloatRect rect, sf::Color colour)
{
	sf::Vertex vertex[5];

	vertex[0] = sf::Vertex(sf::Vector2f(rect.left, rect.top), colour);
	vertex[1] = sf::Vertex(sf::Vector2f(rect.left + rect.width, rect.top), colour);
	vertex[2] = sf::Vertex(sf::Vector2f(rect.left + rect.width, rect.top + rect.height), colour);
	vertex[3] = sf::Vertex(sf::Vector2f(rect.left, rect.top + rect.height), colour);
	vertex[4] = sf::Vertex(sf::Vector2f(rect.left, rect.top), colour);

	target.draw(vertex, 5, sf::LinesStrip);
}
