#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <string> 
#include <array> 

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "Collider.H"
#include "Player.H"
#include "Platform.H"

class GameManager
{
	
public:
	GameManager();
	~GameManager();

	//variables
	bool justOnceInit1=false;
	bool stageContainsRedPlatform = false;

	bool justOnceActiveErase= false;
	bool justOnceActiveErasePlayerBullet= false;
	bool isIncreaseGravityTimerActive = false;
	bool notEnoughGravityChargeActive = false;
	bool justOnceDestroyPinkPlatform = false;
	bool playerWasItTouchByEnemy=false;
	bool doesPinkPlatformShouldBeSpwaned = false;

	float redGravitySpeed = 0.0f;
	float pinkGravitySpeed = 0.0f;
	float gravityTimer = 0.f;
	float gravityTimerMax = 700.f;


	//class
	Player player;

	std::vector<Platform> platforms;
	std::vector<Platform> redPlatforms;
	std::vector<Platform> bluePlatforms;

	std::vector<Platform> pinkPlatforms;
	std::vector<Platform> violetPlatforms;


	Platform platformWhite;
	Platform platformWhite2;
	Platform platformWhiteLittle;
	Platform platformRed;
	Platform platformRedBig;
	Platform platformBlue;
	Platform platformBlueLongHorizontal;

	Platform pinkPlatforme;
	Platform violetPlatforme;

	sf::RenderWindow window;
	sf::Vector2i centerWindow;

	sf::Font font;

	sf::Text textEnergy;
	sf::Text notEnoughGravityCharge;
	sf::Text textKilledEnmiesNumber;
	sf::Text textYouLoose;
	sf::Text textGameTime;

	sf::Text textTutorialShoot;
	sf::Text textTutorialGravityShoot;

	sf::Text textPreviousScore;

	sf::RectangleShape backgroundColor;

	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	sf::Vector2f mousePos;

	//functions
	void InitWindow();
	void InitText();

	
	void LoadCurrentStage();
	void ClearPlatformArray();
	void InitStage1();
	void RenderPlatforms(std::vector<Platform> platforms);
	void MainRender();

	void SpawnRedPlatform();
	void SpawnPinkPlatform();
	void SpawnVioletPlatform();

	void ControlGravity();
	void PlayerInput();
	void ControlCollision();

	void PlayerLoose();
	void CheckIfPlayerCollideWithEnemy(std::vector <Platform> platforms);
	void Respawn();
	void EnemyDied(int enemyIndex);
	void IncreaseGravity();
	void EnemyMove();
	void PinkPlatformeEnemyMove();
	void VioletPlatformeEnemyMove();
	void CheckIfEnemiesIsBelowTheScreen();
	
	
	

private:
	const int groundHeight = 900;
	const float gravitySpeed = 0.6f;
	const float playerGravitySpeed = 0.f;
	
	float jumpVelocity = 0.f;
	float jumpMaxEnergy = 1.0f;

	float enemySpawnTimer=0.f;
	float enemySpawnTimerMax=700.0f;

	float playerLooseTimer = 0.f;
	float playerLooseTimerMax = 700.f;

	float winkTimer = 0;
	float winkTimerMax = 100;
	int winkTimerCount = 0;

	int maxEnemies=10;

	float playedTime=0;
	int displayedPlayTime = 0;
	int gameTimeContainer = 0;

	int hardneesIndex=0;

	bool gameEnded = false;

	int previousScore=0;
};

