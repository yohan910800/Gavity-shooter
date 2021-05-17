#pragma once


#include "Player.h"
#include "Collider.h"


class Exit
{
public:
	Exit(sf::Vector2f size,sf::Color color);
	~Exit();


	float distY;
	float distX;

	//functions 
	void SetPosition(sf::Vector2f newPos);
	void Draw(sf::RenderWindow& window);

	Collider GetCollider() { return Collider(body); }
	int GetY();
	int GetX();

private:
	sf::RectangleShape body;
	Player player;
};

