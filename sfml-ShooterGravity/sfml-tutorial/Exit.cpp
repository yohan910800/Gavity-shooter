#include "Exit.h"



Exit::Exit(sf::Vector2f size, sf::Color color):player({ 40,40 })
{
	body.setFillColor(color);
	body.setSize(size);
	body.setOrigin(size / 2.f);
}

Exit::~Exit()
{
}

void Exit::SetPosition(sf::Vector2f newPos)
{
	body.setPosition(newPos);
}

void Exit::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


int Exit::GetY()
{
	return body.getPosition().y;
}
int Exit::GetX()
{
	return body.getPosition().x;
}
