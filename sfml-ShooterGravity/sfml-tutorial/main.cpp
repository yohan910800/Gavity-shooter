#include "SFML/Audio.hpp"
#include "GameManager.H"

int main()
{
	GameManager gm;
	gm.InitWindow();
	gm.InitText();
	
	int i=0;
	gm.window.setFramerateLimit(256);
	//game loop
	while (gm.window.isOpen())
	{
		gm.LoadCurrentStage();
		sf::Event Event;

		while (gm.window.pollEvent(Event)) {

			switch (Event.type) {
			case sf::Event::Closed:
				gm.window.close();
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (gm.player.projectils.size() < 1) {
						gm.player.Shoot(gm.window);
						gm.textTutorialShoot.setString("");
					}
					gm.notEnoughGravityChargeActive = false;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					gm.textTutorialGravityShoot.setString("");
					if (gm.player.gravityCharge >= 50) {
						gm.gravityTimer = 0.f;
						gm.player.gravityCharge -= 50;
						gm.isIncreaseGravityTimerActive = true;
					}
					else {
						gm.notEnoughGravityChargeActive = true;
					}
				}
			}
		}
		
		if (gm.isIncreaseGravityTimerActive == true) {
			gm.IncreaseGravity();
		}

		gm.ControlCollision();
		gm.EnemyMove();
		gm.VioletPlatformeEnemyMove();
		gm.PinkPlatformeEnemyMove();
		gm.PlayerInput();
		gm.ControlGravity();
		gm.MainRender();
	}	
	//end of the loop
	return 0;
}