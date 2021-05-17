#include "Player.h"



Player::Player(sf::Vector2f size) :projectile({ 40,40 }, { sf::Color::Yellow })
{
	body.setOrigin(size / 2.f);
	body.setSize(size);
	body.setFillColor(sf::Color::Green);
}
Player::~Player()
{
}
void Player::DrawTo(sf::RenderWindow & window)
{
	window.draw(body);
}
void Player::Move(sf::Vector2f distance)
{
	body.move(distance);
}
void Player::SetPosition(sf::Vector2f newPos)
{
	body.setPosition(newPos);
}

void Player::Shoot(sf::RenderWindow & window)
{
	projectile.SetPosition(body.getOrigin());
	projectile.SetPosition({ (float)GetX(),(float)GetY() });
	
	projectils.push_back(projectile);
	
	
}

int Player::GetY()
{
	return body.getPosition().y;
}

int Player::GetX()
{
	return body.getPosition().x;
}

sf::Vector2f Player::PlayerCenter()
{
	return sf::Vector2f(body.getPosition().x+body.getOrigin().x, body.getPosition().y + body.getOrigin().y);
}










