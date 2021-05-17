#include "Game.h"




void Game::InitVariables()
{
	this->window = nullptr;
	// game logic 

	this->points = 0;
	this->enemySpawnTimerMax = 100.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Game::InitEenemies()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f,100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);

}

void Game::InitWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "SFML works!",sf::Style::Titlebar|sf::Style::Close);
	this->window->setFramerateLimit(60);
}



//Constructor/destructors
Game::Game()
{
	this->InitVariables();
	this->InitWindow();
	this->InitEenemies();

	//player.InitPlayer();
}


Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::Running() const
{
	return this->window->isOpen();
}



void Game::SpawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().
			x-this->enemy.getSize().x)),0.f);
	
	this->enemy.setFillColor(sf::Color::Green);

	//spawn the enemy
	this->enemies.push_back(this->enemy);

}


void Game::PollEvents()
{
	while (this->window->pollEvent(this->ev))
	{

		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();

			}
			break;
		}
	}
}

void Game::UpdateMousePos()
{
	/*
	return void

	update the mous position relative to window
	*/
	this->mousPosWindow = sf::Mouse::getPosition(*this->window);

}

void Game::UpdateEnemies()
{
	//update timer  for enemy spawning
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->SpawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}

	//move enemies
	for (auto &e:this->enemies ) {
		e.move(0.f,3.f);
	}

}

void Game::Update()
{
	this->PollEvents();

	//update mouse position
	this->UpdateMousePos();

	this->UpdateEnemies();

	//player.UpdatePlayerInput();

	std::cout << "Mouse pos:" 
		<< sf::Mouse::getPosition(*this->window).x<<" "
		<< sf::Mouse::getPosition(*this->window).y<<"\n";
}

void Game::RenderEnemies()
{
	//rendering all the enemies
	for (auto &e : this->enemies) {
		this->window->draw(e);
	}
}

//void Game::RenderPlayer()
//{
//	this->window->draw(player.body);
//
//}



void Game::Render()
{
	this->window->clear();
	
	//darw game
	this->window->draw(this->enemy);

	this->RenderEnemies();
	//this->RenderPlayer();

	this->window->display();

	
}
