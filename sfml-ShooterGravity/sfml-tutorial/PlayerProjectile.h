#pragma once

#include "Collider.h"

class PlayerProjectile
{
public:
	PlayerProjectile(sf::Vector2f size,sf::Color color);
	~PlayerProjectile();

	sf::Vector2f currVelocity;
	sf::RectangleShape body;

	void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f pos);

	void Move(sf::Vector2f direction);

	int GetX();
	int GetY();

	Collider GetCollider() { return Collider(body); }
};

