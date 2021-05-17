#include "GameManager.h"
//Start
////////////

GameManager::GameManager() :
	player({40,40}),
	platformBlue({ 40,40 }, { sf::Color::Blue }) ,
	platformBlueLongHorizontal({ 400,40 }, { sf::Color::Blue }) ,
	platformRedBig({ 80,80 }, { sf::Color::Red }) ,
	platformWhiteLittle({ 80,40 }, { sf::Color::White }) ,
	
	platformWhite({ 800,40 }, { sf::Color::White }),
	platformWhite2({ 40,800 }, { sf::Color::White }),
	platformRed({ 40,40 }, { sf::Color::Red }),
	pinkPlatforme({250,60}, {255,192,203}),//pink
	violetPlatforme({ 250,500 }, { 127,0,255 }),//violet
	
centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445,
(sf::VideoMode::getDesktopMode().height / 10))
{
	
}
GameManager::~GameManager()
{
}
void GameManager::InitWindow()
{
	window.create
	(sf::VideoMode(900, 900), "SFML gravity", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);
	
}
void GameManager::InitText()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	textEnergy.setFont(font); // font is a sf::Font
	textEnergy.setCharacterSize(24); // in pixels, not points!
	textEnergy.setFillColor(sf::Color::Green);
	textEnergy.setStyle(sf::Text::Bold);
	textEnergy.setPosition(10, 20);

	notEnoughGravityCharge.setFont(font); // font is a sf::Font
	notEnoughGravityCharge.setCharacterSize(44); // in pixels, not points!
	notEnoughGravityCharge.setFillColor(sf::Color::Red);
	notEnoughGravityCharge.setStyle(sf::Text::Bold);
	notEnoughGravityCharge.setPosition(30, 400);

	textKilledEnmiesNumber.setFont(font); // font is a sf::Font
	textKilledEnmiesNumber.setCharacterSize(24); // in pixels, not points!
	textKilledEnmiesNumber.setFillColor(sf::Color::Green);
	textKilledEnmiesNumber.setStyle(sf::Text::Bold);
	textKilledEnmiesNumber.setPosition(10, 50);

	textYouLoose.setFont(font); // font is a sf::Font
	textYouLoose.setCharacterSize(64); // in pixels, not points!
	textYouLoose.setFillColor(sf::Color::Red);
	textYouLoose.setStyle(sf::Text::Bold);
	textYouLoose.setPosition(250, 400);

	textGameTime.setFont(font); // font is a sf::Font
	textGameTime.setCharacterSize(24); // in pixels, not points!
	textGameTime.setFillColor(sf::Color::Yellow);
	textGameTime.setStyle(sf::Text::Bold);
	textGameTime.setPosition(10, 100);
	
	textTutorialShoot.setFont(font); // font is a sf::Font
	textTutorialShoot.setCharacterSize(24); // in pixels, not points!
	textTutorialShoot.setFillColor(sf::Color::Magenta);
	textTutorialShoot.setStyle(sf::Text::Bold);
	textTutorialShoot.setPosition(10, 200);
	
	textTutorialGravityShoot.setFont(font); // font is a sf::Font
	textTutorialGravityShoot.setCharacterSize(24); // in pixels, not points!
	textTutorialGravityShoot.setFillColor(sf::Color::Magenta);
	textTutorialGravityShoot.setStyle(sf::Text::Bold);
	textTutorialGravityShoot.setPosition(10, 300);

	textPreviousScore.setFont(font); // font is a sf::Font
	textPreviousScore.setCharacterSize(24); // in pixels, not points!
	textPreviousScore.setFillColor(sf::Color::Red);
	textPreviousScore.setStyle(sf::Text::Bold);
	textPreviousScore.setPosition(10, 400);

}

///////
////////


//Initialize stages 
////////////
////////////
void GameManager::InitStage1()
{
	//Vector setting
	//redPlatforms.clear();
	ClearPlatformArray();
	playerLooseTimer = 0.f;
	player.gravityCharge = 0.f;
	gravityTimer = 0.f;

	isIncreaseGravityTimerActive = false;
	backgroundColor.setSize({ 0, 0 });
	playerWasItTouchByEnemy = false;
	previousScore = player.enemyKilledNum;
	player.enemyKilledNum = 0;
	winkTimerCount = 0;
	hardneesIndex = 0;
	gameTimeContainer = 0;
	playedTime = 0;
	//
	//Gravity setting
	stageContainsRedPlatform = false;
	//
	//GameObject position Setting
	player.SetPosition({ 450,450 });
	//
	textTutorialShoot.setString("Left click to shoot");
	textTutorialGravityShoot.setString("Right click to increase gravity ");

	notEnoughGravityCharge.setString("YOU NEED MORE GRAVITY CHARGE");
	textYouLoose.setString("YOU DIED");
	textPreviousScore.setString("Previous score: " + std::to_string(previousScore));
}

void GameManager::LoadCurrentStage()
{
	if (justOnceInit1 == false) {
		InitStage1();
		justOnceInit1 = true;
	}

	//set game time
	float displayedEnergy = jumpMaxEnergy - jumpVelocity;
	displayedPlayTime = playedTime / 400;
	gameTimeContainer = displayedPlayTime;

	if (gameTimeContainer >= 15) {
		if (gameTimeContainer % 5 == 0 && gameTimeContainer != 0) {
			doesPinkPlatformShouldBeSpwaned = true;
		}
	}
	playedTime++;
	////

	//handle energy
	if (displayedEnergy < 0) {
		displayedEnergy = 0;
	}
	////
	//set Text
	textKilledEnmiesNumber.setString("Number of enemy killed : " + std::to_string(player.enemyKilledNum));
	textEnergy.setString("GRAVITY CHARGE : "+std::to_string(player.gravityCharge)+"%");
	textGameTime.setString("Time played : "+std::to_string(displayedPlayTime)+"s");
	///
	//Spawn enmies
	SpawnRedPlatform();
	SpawnVioletPlatform();
	if (doesPinkPlatformShouldBeSpwaned == true) {
		SpawnPinkPlatform();
	}
	////
}

void GameManager::ClearPlatformArray()
{
	redPlatforms.clear();
	pinkPlatforms.clear();
	platforms.clear();
	bluePlatforms.clear();
	violetPlatforms.clear();
}

////////////
////////////

// Render Elements
//////////////
////////////////

void GameManager::RenderPlatforms(std::vector<Platform> platforms)
{
	for (auto platforme : platforms) {
		platforme.Draw(window);
	}
}

void GameManager::MainRender()
{
	window.clear();
	window.draw(backgroundColor);// needss to be in the uppest line to be displayer before the others gameobjects
	
	RenderPlatforms(platforms);
	RenderPlatforms(redPlatforms);
	RenderPlatforms(bluePlatforms);
	RenderPlatforms(pinkPlatforms);
	RenderPlatforms(violetPlatforms);
	
	if (player.projectils.size() > 0) {
		for (auto projectile : player.projectils) {
			projectile.Draw(window);
		}
	}
	if (notEnoughGravityChargeActive == true) {
		window.draw(notEnoughGravityCharge);
	}
	window.draw(textKilledEnmiesNumber);
	window.draw(textEnergy);
	window.draw(textGameTime);
	window.draw(textTutorialShoot);
	window.draw(textTutorialGravityShoot);
	window.draw(textPreviousScore);
	player.DrawTo(window);
	if (playerWasItTouchByEnemy == true) {
		window.draw(textYouLoose);
	}
	window.display();
}
//spawn enmies
void GameManager::SpawnRedPlatform()
{
	if (redPlatforms.size() < maxEnemies) {
		if (enemySpawnTimer >= enemySpawnTimerMax) {
			for (int i = 0; i < hardneesIndex; i++) {
				//choose spawn position
				int sideNum = rand() % 4;
				switch (sideNum) {
				case 0:
					platformRed.SetPosition({ static_cast <float>(rand() % 900),static_cast <float>(rand() % 100) });
					break;
				case 1:
					platformRed.SetPosition({ static_cast <float>(rand() % 900),static_cast <float>(rand() % 800 + 900) });
					break;
				case 2:
					platformRed.SetPosition({ static_cast <float>(rand() % 100),static_cast <float>(rand() % 900) });
					
					break;
				case 3:
					platformRed.SetPosition({ static_cast <float>(rand() % 800 + 900),static_cast <float>(rand() % 900) });
					break;
				}
				//spawn the enemy
				redPlatforms.push_back(platformRed);
				redPlatforms[0].speed = 0.003f;
			}
			hardneesIndex++;
			enemySpawnTimer = 0.f;
		}
		else {
			enemySpawnTimer += 1.f;
		}
	}
}
void GameManager::SpawnPinkPlatform()
{
	if (pinkPlatforms.size() < maxEnemies) {
		if (enemySpawnTimer >= enemySpawnTimerMax) {
			//make the pink platform spawn rendomely every  5 seconds
			int randomPinkPlatformNum = rand() % 3;
			switch (randomPinkPlatformNum) {
			case 0:
				pinkPlatforms.push_back(pinkPlatforme);
				pinkPlatforms.push_back(pinkPlatforme);
				pinkPlatforms[0].SetPosition({ (float)player.GetX() - 400.0f,(float)player.GetY() });
				pinkPlatforms[1].SetPosition({ (float)player.GetX() + 400.0f,(float)player.GetY() });
				break;
			case 1:
				return;
				break;
			case 2:
				return;
				break;
			}
			justOnceDestroyPinkPlatform = false;
			enemySpawnTimer = 0.f;
		}
		else {
			enemySpawnTimer += 1.f;
		}
	}
}
void GameManager::SpawnVioletPlatform()
{
	if (violetPlatforms.size() < maxEnemies) {
		if (enemySpawnTimer >= enemySpawnTimerMax) {
			int randomVioletPlatformNum = rand() % 10+1;

			switch (randomVioletPlatformNum) {
			case 0:
				violetPlatforme.SetPosition({ 100 ,0 });
				violetPlatforms.push_back(violetPlatforme);
				break;
			case 1:
				violetPlatforme.SetPosition({ 400 ,0 });
				violetPlatforms.push_back(violetPlatforme);
				break;
			case 2:
				violetPlatforme.SetPosition({ 800 ,0 });
				violetPlatforms.push_back(violetPlatforme);
				break;
			default:
				return;
				break;
			}
			enemySpawnTimer = 0.f;
		}
		else {
			enemySpawnTimer += 1.f;
		}
	}
}
//////////////
////////////////


//System
////////////
//////////
void GameManager::ControlGravity()
{
	if (player.GetY() < groundHeight) {
		player.Move({ 0.f, playerGravitySpeed });
	}
	for (auto bluePlatform = bluePlatforms.begin(); bluePlatform != bluePlatforms.end(); ++bluePlatform) {
		if (bluePlatform->GetY() < groundHeight) {
			bluePlatform->Move({ 0.f, gravitySpeed });
		}
	}
	for (auto redPlatform = redPlatforms.begin(); redPlatform != redPlatforms.end(); ++redPlatform) {
		if (redPlatform->GetY() < groundHeight) {
			redPlatform->Move({ 0.f, redGravitySpeed });
		}
	}
	for (auto pinkPlatform = pinkPlatforms.begin(); pinkPlatform != pinkPlatforms.end(); ++pinkPlatform) {
		if (pinkPlatform->GetY() < groundHeight) {
			pinkPlatform->Move({ 0.f, pinkGravitySpeed });
		}
	}
}
void GameManager::PlayerInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.Move({ player.speed ,0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.Move({ -player.speed ,0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.Move({0,-player.speed });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.Move({ 0,player.speed });
	}
}
void GameManager::ControlCollision()
{
	mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
	aimDir = mousePos - player.PlayerCenter();
	aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

	for (size_t j = 0; j < player.projectils.size(); j++) {

		player.projectils[j].currVelocity = aimDirNorm * 2.f;
		player.projectils[j].Move(player.projectils[j].currVelocity);

		if (player.projectils[j].body.getPosition().x<0 ||
			player.projectils[j].body.getPosition().x>window.getSize().x ||
			player.projectils[j].body.getPosition().y<0 ||
			player.projectils[j].body.getPosition().y>window.getSize().y)
		{
			player.projectils.erase(player.projectils.begin() + j);
		}
	}

	if (redPlatforms.empty() == false && player.projectils.empty() == false) {
		for (int i = 0; i < redPlatforms.size(); i++) {
			for (size_t j = 0; j < player.projectils.size(); j++){
				if (redPlatforms[i].GetCollider().CheckCollision(player.projectils[j].GetCollider(), 1.0f) == true) {
						justOnceActiveErase = true;
						justOnceActiveErasePlayerBullet = true;
						EnemyDied(i);
				}
			}
		}
	}
	CheckIfPlayerCollideWithEnemy(redPlatforms);
	CheckIfPlayerCollideWithEnemy(pinkPlatforms);
	CheckIfPlayerCollideWithEnemy(violetPlatforms);
	CheckIfEnemiesIsBelowTheScreen();
	if (playerWasItTouchByEnemy==true) {
		PlayerLoose();
	}
}
void GameManager::PlayerLoose()
{
	if (playerLooseTimer < playerLooseTimerMax) {
		backgroundColor.setFillColor(sf::Color::Red);
		backgroundColor.setPosition({ 0,0 });
		if (winkTimerCount < 5) {
			if (winkTimer < winkTimerMax) {
				if (winkTimer < winkTimerMax / 2) {
					backgroundColor.setSize({ 0, 0 });
				}
				else{
					backgroundColor.setSize({ 900, 900 });
				}
				winkTimer += 1.f;
			}
			else {
				winkTimerCount += 1;
				winkTimer = 0.f;
			}
		}
		playerLooseTimer += 1.f;
	}
	else {
		Respawn();
	}
}
void GameManager::CheckIfPlayerCollideWithEnemy(std::vector<Platform> platforms)
{
	for (auto platform : platforms) {
		if (platform.GetCollider().CheckCollision(player.GetCollider(), 1.0f) == true) {
			doesPinkPlatformShouldBeSpwaned = false;
			playerWasItTouchByEnemy = true;
		}
	}
}
void GameManager::Respawn()
{
	justOnceInit1 = false;
}
void GameManager::EnemyDied(int enemyIndex)
{
	if (justOnceActiveErase == true) {
		if (redPlatforms.empty() == false) {
			redPlatforms.erase(redPlatforms.begin() + enemyIndex);
			if (player.gravityCharge <= 100) {
				player.gravityCharge += 10;
				if (player.gravityCharge > 100) {
					player.gravityCharge = 100;
				}
			}
			player.enemyKilledNum++;
		}
		justOnceActiveErase = false;
	}
}
void GameManager::IncreaseGravity()
{
	if (gravityTimer > gravityTimerMax) {
		redGravitySpeed = 0.f;
		pinkGravitySpeed = 0.f;
		backgroundColor.setSize({ 0,0 });
		isIncreaseGravityTimerActive = false;
	}
	else {
		gravityTimer +=1;
		redGravitySpeed = 1.9f;
		pinkGravitySpeed = 2.9f;
		backgroundColor.setFillColor(sf::Color::Blue);
		backgroundColor.setSize({900,900});
	}
}
void GameManager::EnemyMove()
{
	for (size_t i = 0; i < redPlatforms.size(); i++) {
		redPlatforms[i].Move({ ((float)player.GetX() - (float)redPlatforms[i].GetX())*redPlatforms[i].speed,
			((float)player.GetY() - (float)redPlatforms[i].GetY())*redPlatforms[i].speed });
	}
}
void GameManager::PinkPlatformeEnemyMove()
{
	if (pinkPlatforms.size() > 1) {
		if (justOnceDestroyPinkPlatform == false) {
			pinkPlatforms[0].speed = 0.001f;
			pinkPlatforms[1].speed = 0.001f;
			if (pinkPlatforms[0].GetCollider().CheckCollision(pinkPlatforms[1].GetCollider(), 1.0f) == false) {
				pinkPlatforms[0].Move({ ((float)pinkPlatforms[1].GetX() - (float)pinkPlatforms[0].GetX())*pinkPlatforms[0].speed,
				((float)pinkPlatforms[1].GetY() - (float)pinkPlatforms[0].GetY())*pinkPlatforms[0].speed });

				pinkPlatforms[1].Move({ ((float)pinkPlatforms[0].GetX() - (float)pinkPlatforms[1].GetX())*pinkPlatforms[1].speed,
				((float)pinkPlatforms[0].GetY() - (float)pinkPlatforms[1].GetY())*pinkPlatforms[1].speed });
			}
			else {
				pinkPlatforms.erase(pinkPlatforms.begin() + 0);
				pinkPlatforms.erase(pinkPlatforms.begin() + 0);
				doesPinkPlatformShouldBeSpwaned = false;

				justOnceDestroyPinkPlatform = true;
			}
		}
	}
}
void GameManager::VioletPlatformeEnemyMove()
{
	if (violetPlatforms.empty() == false) {
		for (int i = 0; i < violetPlatforms.size(); i++) {
			if (violetPlatforms[i].GetY() >= 650.0f) {
				violetPlatforms.erase(violetPlatforms.begin()+i);
			}
			else {
				violetPlatforms[i].Move({ 0.0f,(900.0f - (float)violetPlatforms[i].GetY())*violetPlatforms[i].speed });
			}
		}
	}
}
void GameManager::CheckIfEnemiesIsBelowTheScreen()
{
	for (int i = 0; i < redPlatforms.size(); i++) {
		if (redPlatforms[i].GetY() > groundHeight) {
			redPlatforms.erase(redPlatforms.begin() + i);
			player.enemyKilledNum++;
		}
	}
	for (int i = 0; i < pinkPlatforms.size(); i++) {
		if (pinkPlatforms[i].GetY() > groundHeight) {
			pinkPlatforms.erase(pinkPlatforms.begin() + i);
		}
	}
}

////////////
//////////
