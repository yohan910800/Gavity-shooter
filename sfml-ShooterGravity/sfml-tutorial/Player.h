#pragma once

#include "Collider.h"
#include "PlayerProjectile.h"


class Player
{
public:
	Player(sf::Vector2f size);
	~Player();

	//variables
	sf::RectangleShape body;

	std::vector<PlayerProjectile> projectils;

	PlayerProjectile projectile;
	
	const float speed=0.9f;
	const float jumpStrenght=0.6f;
	float gravityCharge = 0.0f;
	int jumpCounter = 0;
	int projectileIndex=0;
	int enemyKilledNum = 0;

	//function
	Collider GetCollider() { return Collider(body); }

	void DrawTo(sf::RenderWindow &window);
	void Move(sf::Vector2f distance);
	void SetPosition(sf::Vector2f newPos);
	void Shoot(sf::RenderWindow & window);
	int GetY();
	int GetX();
	sf::Vector2f PlayerCenter();

};

