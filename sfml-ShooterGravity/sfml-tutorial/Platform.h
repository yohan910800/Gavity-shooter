#pragma once

#include "Collider.h"


class Platform
{
public:
	Platform(sf::Vector2f size, sf::Color color);
	~Platform();


	float speed = 0.001f;
	sf::RectangleShape body;
	//Functions
	void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f newPos);
	void Move(sf::Vector2f distance);
	
	float GetSizeX();
	int GetY();
	int GetX();

	Collider GetCollider() { return Collider(body); }
		
	
};

