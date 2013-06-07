#include "ClickableText.h"

using namespace std;

sf::Color ClickableText::normalColour = sf::Color::White;
sf::Color ClickableText::hoverColour = sf::Color(160, 160, 160);
sf::Color ClickableText::clickedColour = sf::Color(80, 80, 80);

ClickableText::ClickableText(string text, sf::Vector2f position, unsigned int fontSize, sf::Font* font, float borderSize)
{
	this->text.setString(text);
	this->text.setPosition(position);
	this->text.setCharacterSize(fontSize);

	if(font != 0)
		this->text.setFont(*font);

	this->borderSize = borderSize;
	updateBoundingBox();
}
ClickableText::~ClickableText()
{

}
void ClickableText::unhovered()
{
	text.setColor(normalColour);
}
void ClickableText::hovered()
{
	text.setColor(hoverColour);
}
void ClickableText::clicked()
{
	text.setColor(clickedColour);
}
void ClickableText::updateBoundingBox()
{
	rect = text.getGlobalBounds();

	rect.left -= borderSize;
	rect.top -= borderSize;
	rect.width += borderSize;
	rect.height += borderSize;
}
void ClickableText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text);
}
