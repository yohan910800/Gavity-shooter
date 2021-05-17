#include "Platform.h"

Platform::Platform( sf::Vector2f size,sf::Color color)
{
	body.setFillColor(color);
	body.setSize(size);
	body.setOrigin(size/2.f);
}

Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow & window)
{
	//body.setFillColor(sf::Color::Blue);
	window.draw(body);
}

void Platform::SetPosition(sf::Vector2f newPos)
{
	body.setPosition(newPos);
}

void Platform::Move(sf::Vector2f distance)
{
	body.move(distance);
}


float Platform::GetSizeX()
{
	return body.getSize().x;
}

int Platform::GetY()
{
	return body.getPosition().y;
}

int Platform::GetX()
{
	return body.getPosition().x;
}
