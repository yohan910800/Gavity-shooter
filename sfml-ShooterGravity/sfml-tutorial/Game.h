#pragma once

/*
Calss that act as game engine
*/

#include <iostream>
#include <vector>
#include <ctime>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//#include "Player.h"
#include "Platform.h"


class Game
{

private:
	
	//Variables
	//Window
	//sf::RenderWindow*window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousPosWindow;

	// Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//private functions
	void InitWindow();
	void InitVariables();
	void InitEenemies();

public:
	//Constructors/Destructors
	Game();
	~Game();


	//GameObject
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//variable
	sf::RenderWindow*window;


	//Player player;

	//Accessors
	const bool Running() const;

	//Functions

	void SpawnEnemy();
	void PollEvents();
	void UpdateMousePos();
	void UpdateEnemies();
	void Update();
	void RenderEnemies();
	//void RenderPlayer();
	void Render();
};

