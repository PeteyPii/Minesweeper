#include "ClickableButton.h"

ClickableButton::ClickableButton(sf::Texture *texture, sf::Vector2f position, sf::Vector2f size)
{
	if(texture != 0)
	{
		sprite.setTexture(*texture);
		sprite.setScale(sf::Vector2f((4 * size.x) / texture->getSize().x, size.y / texture->getSize().y));
	}

	sprite.setPosition(position);

	if(texture != 0)
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(sprite.getTexture()->getSize().x / 4, sprite.getTexture()->getSize().y)));

	rect = sf::FloatRect(position, size);
}
ClickableButton::~ClickableButton()
{

}
void ClickableButton::unhovered()
{
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(sprite.getTexture()->getSize().x / 4, sprite.getTexture()->getSize().y)));
}
void ClickableButton::hovered()
{
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(sprite.getTexture()->getSize().x / 4, 0), sf::Vector2i(sprite.getTexture()->getSize().x / 4, sprite.getTexture()->getSize().y)));
}
void ClickableButton::clicked()
{
	sprite.setTextureRect(sf::IntRect(sf::Vector2i(sprite.getTexture()->getSize().x / 2, 0), sf::Vector2i(sprite.getTexture()->getSize().x / 4, sprite.getTexture()->getSize().y)));
}
void ClickableButton::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
	rect = sf::FloatRect(position, sf::Vector2f(rect.width, rect.height));
}
void ClickableButton::setPosition(float positionX, float positionY)
{
	setPosition(sf::Vector2f(positionX, positionY));
}
void ClickableButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite);
}
