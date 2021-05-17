#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	bool isItColliding = false;

	//functions
	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider other,float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize()/2.f; }

private:
	sf::RectangleShape& body;


};

