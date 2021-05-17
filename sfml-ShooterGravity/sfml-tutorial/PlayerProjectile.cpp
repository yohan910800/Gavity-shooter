#include "PlayerProjectile.h"

PlayerProjectile::PlayerProjectile(sf::Vector2f size, sf::Color color)
	:currVelocity(0.f,0.f)
{
	body.setFillColor(color);
	body.setSize(size);
	body.setOrigin(size / 2.f);
}


PlayerProjectile::~PlayerProjectile()
{
}

void PlayerProjectile::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void PlayerProjectile::SetPosition(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void PlayerProjectile::Move(sf::Vector2f direction)
{
	body.move(direction);
}

int PlayerProjectile::GetX()
{
	return body.getPosition().x;
}

int PlayerProjectile::GetY()
{
	return body.getPosition().y;
}


