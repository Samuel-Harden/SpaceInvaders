#include<time.h>

#include "SpriteManager.h"
#include "CollisionManager.h"

#include "Actions.h"

// Game Objects
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "MotherShip.h"
#include "Bunker.h"

// Sound + Audio Assets
#include "SoundAssets.h"
#include "SpriteAssets.h"



SpriteManager::SpriteManager(int& _totalEnemies, int& _totalBunkers,
	int& _totalEnemyBullets, int& _width, int& _height)
{
	srand(time(NULL));
	totalEnemyBullets = _totalEnemyBullets;
	enemies.reserve(_totalEnemies);
	enemyBullets.reserve(totalEnemyBullets);
	bunkers.reserve(_totalBunkers);
	width = _width;
	height = _height;

	// Set up assets for sprites + audio
	audio_manager = std::make_unique<AudioManager>();
	sound_assets = std::make_unique<SoundAssets>();
	sprite_assets = std::make_unique<SpriteAssets>();
	collision_manager = std::make_unique<CollisionManager>();

	counter = 0;
	score = 0;
	deadEnemies = 0;
	currentLevel = 1;
	spriteSwitch = true;
	moveLeft = false;
	moveRight = true;
	moveDown = false;
}



SpriteManager::~SpriteManager()
{

}



void SpriteManager::generatePlayer(std::shared_ptr<ASGE::Renderer>& renderer)
{
	int plsizeX = 50;
	int plsizeY = 25;
	player_one = std::make_unique<Player>();
	player_one->setGameDimentions(width, height);
	player_one->loadSprite(renderer, sprite_assets->playerSprite);
	player_one->resetPos();
	player_one->setSize(plsizeX, plsizeY);
}



void SpriteManager::generateGameObjects(std::shared_ptr<ASGE::Renderer>&
	renderer, int& _totalEnemies, int& _totalBunkers)
{
	generatePlayer(renderer);
	generateEnemies(renderer, _totalEnemies);
	generateMotherShip(renderer);
	generateBullet(renderer);
	generateBunkers(renderer, _totalBunkers);
	generateEnemyBullets(renderer);
}



void SpriteManager::generateBunkers(std::shared_ptr<ASGE::Renderer>& renderer,
	int _totalBunkers)
{
	totalBunkers = _totalBunkers;
	int counter = 0;
	int alienType = 0;
	int sizeX = 50;
	int sizeY = 20;
	int posX = width / 5;
	int posY = height - 150;
	int spriteNo = 0;

	// Create the Bunkers
	for (int i = 0; i < totalBunkers; i++)
	{
		bunker = new Bunker;

		bunker->loadSprite(renderer, sprite_assets->bunker1,
			sprite_assets->bunker2, sprite_assets->bunker3);

		bunker->setSize(sizeX, sizeY);
		bunker->setGameDimentions(width, height);
		bunker->setPosX(posX);
		bunker->setPosY(posY);
		posX += ((width / 5) - ((bunker->getSizeX() / 2)));
		bunker->setSpriteNo(spriteNo);

		bunkers.push_back(bunker);
	}
}



void SpriteManager::generateMotherShip(std::shared_ptr<ASGE::Renderer>& renderer)
{
	int mssizeX = 48;
	int mssizeY = 21;
	mother_ship = std::make_unique<MotherShip>();
	mother_ship->setGameDimentions(width, height);
	mother_ship->loadSprite(renderer, sprite_assets->motherShip);
	mother_ship->resetPos();
	mother_ship->setSize(mssizeX, mssizeY);
}



void SpriteManager::generateBullet(std::shared_ptr<ASGE::Renderer>& renderer)
{
	int bulSizeX = 5;
	int bulSizeY = 18;
	player_bullet = std::make_unique<Bullet>();
	player_bullet->loadSprite(renderer, sprite_assets->bullet);
	player_bullet->setSize(bulSizeX, bulSizeY);
}



void SpriteManager::generateEnemyBullets(std::shared_ptr<ASGE::Renderer>&
	renderer)
{
	int bulSizeX = 5;
	int bulSizeY = 18;

	for (int i = 0; i < totalEnemyBullets; i++)
	{
		enemy_bullet = new Bullet;
		enemy_bullet->loadSprite(renderer, sprite_assets->bullet);
		enemy_bullet->setSize(bulSizeX, bulSizeY);

		enemyBullets.push_back(enemy_bullet);
	}
}



void SpriteManager::generateEnemies(std::shared_ptr<ASGE::Renderer>& renderer,
	int _totalEnemies)
{
	totalEnemies = _totalEnemies;
	int counter = 0;
	int alienType = 0;
	int ensizeX = 24;
	int ensizeY = 16;
	int posX = 20;
	int posY = 100;
	int rowNo = 0;
	int columnNo = 0;

	// Create the aliens
	for (int i = 0; i < totalEnemies; i++)
	{
		alien = new Enemy;

		if (alienType == 0 || alienType == 3)
		{
			alien->loadSprite(renderer, sprite_assets->alien1a,
				sprite_assets->alien1b);
		}

		if (alienType == 1 || alienType == 4)
		{
			alien->loadSprite(renderer, sprite_assets->alien2a,
				sprite_assets->alien2b);
		}

		if (alienType == 2)
		{
			alien->loadSprite(renderer, sprite_assets->alien3a,
				sprite_assets->alien3b);
		}

		alien->setSize(ensizeX, ensizeY);
		alien->setPosX(posX);
		alien->setPosY(posY);

		alien->setRow(rowNo);
		alien->setColumn(columnNo);
		posX += 36;

		enemies.push_back(alien);

		columnNo++;
		counter++;

		if (counter == 11)
		{
			posX = 20;
			posY += 36;
			counter = 0;
			alienType++;
			rowNo++;
			columnNo = 0;
		}
	}
}



void SpriteManager::renderEnemies(std::shared_ptr<ASGE::Renderer>& renderer)
{
	for (int i = 0; i < totalEnemies; i++)
	{
		if (enemies[i]->isAlive() == true)
		{
			enemies[i]->getSprite(spriteSwitch)->render(renderer);
		}
	}
}



void SpriteManager::renderBunkers(std::shared_ptr<ASGE::Renderer>& renderer)
{
	for (int i = 0; i < totalBunkers; i++)
	{
		if (bunkers[i]->isAlive() == true)
		{
			bunkers[i]->getSprite()->render(renderer);
		}
	}
}



void SpriteManager::renderPlayer(std::shared_ptr<ASGE::Renderer>& renderer) const
{
	player_one->getSprite()->render(renderer);
}



void SpriteManager::renderMotherShip(std::shared_ptr<ASGE::Renderer>&
	renderer) const
{
	mother_ship->getSprite()->render(renderer);
}



void SpriteManager::renderBullets(std::shared_ptr<ASGE::Renderer>& renderer)
{
	player_bullet->getSprite()->render(renderer);

}



void SpriteManager::renderEnemyBullets(std::shared_ptr<ASGE::Renderer>& renderer)
{
	for (int i = 0; i < totalEnemyBullets; i++)
	{
		if (enemyBullets[i]->isAlive() == true)
		{
			enemyBullets[i]->getSprite()->render(renderer);
		}
	}
}



void SpriteManager::resetGameObjects()
{
	player_one->resetPos();

	mother_ship->resetObject();

	player_bullet->resetObject();

	// Also reset the counter used for counting enemy movement
	counter = 0;

	// And reset Enemy movement Bool's & state
	enemy_state = EnemyState::RIGHT;
	spriteSwitch = true;
	moveLeft = false;
	moveRight = true;
	moveDown = false;

	int posX = 20;
	int posY = 100;
	int alienNo = 0;

	// Reset Bunker Health
	for (int i = 0; i < totalBunkers; i++)
	{
		bunkers[i]->bunkerReset();
	}

	// Reset Enemy Bullets
	for (int i = 0; i < totalEnemyBullets; i++)
	{
		enemyBullets[i]->resetObject();
	}

	// Reset the aliens actual position
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->setPosX(posX);
		enemies[i]->setPosY(posY);
		posX += 36;
		enemies[i]->setAlive();

		alienNo++;

		if (alienNo == 11)
		{
			posX = 20;
			posY += 36;
			alienNo = 0;
		}
	}
}



void SpriteManager::resetPlayerLives()
{
	player_one->resetLives();
}



void SpriteManager::resetScore()
{
	score = 0;
}



void SpriteManager::resetLevelWon()
{
	deadEnemies = 0;
}



void SpriteManager::resetCurrentLevel()
{
	currentLevel = 1;
}



void SpriteManager::movePlayerLeft() const
{
	player_one->moveLeft();
}



void SpriteManager::movePlayerRight() const
{
	player_one->moveRight();
}



void SpriteManager::updateEnemyPositions(int& width, int& height)
{
	// change sprite each time they move
	changeSprite();

	if (enemy_state == EnemyState::RIGHT)
	{
		moveEnemiesRight();
		for (int i = 0; i < totalEnemies; i++)
		{
			if (enemies[i]->isAlive() == true)
			{
				if (enemies[i]->getPosX() > 
					((width - 50) - (enemies[i]->getSizeX() / 2)))
				{
					enemy_state = EnemyState::DOWN;
					return;
				}
			}
		}
	}

	if (enemy_state == EnemyState::LEFT)
	{
		moveEnemiesLeft();
		for (int i = 0; i < totalEnemies; i++)
		{
			if (enemies[i]->isAlive() == true)
			{
				if (enemies[i]->getPosX() < 50)
				{
					enemy_state = EnemyState::DOWN;
					return;
				}
			}
		}
	}

	if (enemy_state == EnemyState::DOWN)
	{
		moveEnemiesDown();

		if (moveRight == true)
		{
			moveRight = false;
			moveLeft = true;
			enemy_state = EnemyState::LEFT;
			counter = 0;
			return;
		}

		if (moveLeft == true)
		{
			moveLeft = false;
			moveRight = true;
			enemy_state = EnemyState::RIGHT;
			counter = 0;
			return;
		}
	}
}



void SpriteManager::update()
{
	player_bullet->tick();

	for (int i = 0; i < totalEnemyBullets; i++)
	{
		if (enemyBullets[i]->isAlive() == true)
		{
			enemyBullets[i]->tick();
		}
	}

	spawnMotherShip();
	spawnEnemyBullet();

	if (mother_ship->isAlive() == true)
	{
		mother_ship->tick();
	}

	// Check if anything has been hit
	checkEnemyHit();
	checkPlayerHit();
	checkMotherShipHit();
	checkBunkerHitPlayer();
	checkBunkerHitEnemy();
}



void SpriteManager::firePlayerBullet()
{
	audio_manager->playAudio(sound_assets->playerFire);

	player_bullet->spawn(player_one->getSprite()->
		position[0], player_one->getSprite()->position[1],
		player_one->getSprite()->size[0]);

}



void SpriteManager::moveEnemiesRight() const
{
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->moveRight();
	}
}



void SpriteManager::moveEnemiesLeft() const
{
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->moveLeft();
	}
}



void SpriteManager::moveEnemiesDown() const
{
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->moveDown();
	}
}



// Used to change the Aliens sprite (animation)
void SpriteManager::changeSprite()
{
	switch (spriteSwitch == true)
	{
		case true:
		{
			spriteSwitch = false;
			break;
		}

		case false:
		{
			spriteSwitch = true;
			break;
		}

	}
}



bool SpriteManager::playerBulletAlive()
{
	if (player_bullet->isAlive() == true)
	{
		return true;
	}
	else
		return false;
}



bool SpriteManager::motherShipAlive()
{
	if (mother_ship->isAlive() == true)
	{
		return true;
	}
	else
		return false;
}



void SpriteManager::checkEnemyHit()
{
	// Check the bullet is active first
	if (player_bullet->isAlive() == true)
	{
		// select next enemy
		for (int i = 0; i < totalEnemies; i++)
		{

			if (enemies[i]->isAlive() == true)
			{
				// Checks to see it the 2 objects are colliding
				if (collision_manager->checkCollision(enemies[i]->getSizeX(),
					enemies[i]->getSizeY(), enemies[i]->getPosX(),
					enemies[i]->getPosY(), player_bullet->getSizeX(),
					player_bullet->getSizeY(), player_bullet->getPosX(),
					player_bullet->getPosY()) == true)
				{
					// destroy selected enemy
					enemies[i]->resetObject();
					deadEnemies += 1;

					// Play Death Audio for alien
					audio_manager->playAudio(sound_assets->alienHit);

					score += 100;
					// destroy the players bullet
					if (deadEnemies != totalEnemies)
					{
						player_bullet->resetObject();
					}

					player_bullet->resetObject();

					// If the enemy killed was the last enemy in the wave
					if (deadEnemies == totalEnemies)
					{
						player_one->addLife();
						currentLevel++;
						audio_manager->playAudio(sound_assets->levelWon);
						game_state = GameState::LEVEL_WON;
					}
					break;
				}
			}
		}
	}
}



void SpriteManager::checkMotherShipHit()
{
	// Check the bullet is active first
	if (player_bullet->isAlive() == true)
	{
		// see if the mothership is alive or not
		if (mother_ship->isAlive() == true)
		{
			// Checks to see it the 2 objects are colliding
			if (collision_manager->checkCollision(mother_ship->getSizeX(),
				mother_ship->getSizeY(), mother_ship->getPosX(),
				mother_ship->getPosY(), player_bullet->getSizeX(),
				player_bullet->getSizeY(), player_bullet->getPosX(),
				player_bullet->getPosY()) == true)
			{
				// destroy MotherShip
				mother_ship->resetObject();

				// Play death audio for mothership
				audio_manager->playAudio(sound_assets->alienHit);

				score += 500;
				// destroy the players bullet
				player_bullet->resetObject();
			}
		}
	}
}



void SpriteManager::checkBunkerHitPlayer()
{
	// Check the Players bullet is active first
	if (player_bullet->isAlive() == true)
	{
		// select next Bunker
		for (int i = 0; i < totalBunkers; i++)
		{
			// see if Bunker is alive or not
			if (bunkers[i]->isAlive() == true)
			{
				// Checks to see it the 2 objects are colliding
				if (collision_manager->checkCollision(bunkers[i]->getSizeX(),
					bunkers[i]->getSizeY(), bunkers[i]->getPosX(),
					bunkers[i]->getPosY(), player_bullet->getSizeX(),
					player_bullet->getSizeY(), player_bullet->getPosX(),
					player_bullet->getPosY()) == true)
				{
					// Damage/Destroy the bunker
					bunkers[i]->setLife();

					// Play Bunker hit audio
					audio_manager->playAudio(sound_assets->bunkerHit);

					// destroy the players bullet
					player_bullet->resetObject();
					break;
				}
			}
		}
	}
}



void SpriteManager::checkPlayerHit()
{
	// Check the Enemies bullets
	for (int i = 0; i < totalEnemyBullets; i++)
	{
		// Check an Enemy bullet is active
		if (enemyBullets[i]->isAlive() == true)
		{
			// Checks to see it the 2 objects are colliding
			if (collision_manager->checkCollision(player_one->getSizeX(),
				player_one->getSizeY(), player_one->getPosX(),
				player_one->getPosY(), enemyBullets[i]->getSizeX(),
				enemyBullets[i]->getSizeY(), enemyBullets[i]->getPosX(),
				enemyBullets[i]->getPosY()) == true)
			{
				// Kill the player (Lose a life)
				player_one->playerHit();

				if (player_one->getLives() > 0)
				{
					audio_manager->playAudio(sound_assets->playerHit);
				}

				if (player_one->getLives() <= 0)
				{
					audio_manager->playAudio(sound_assets->gameOver);
				}

				// destroy the enemies bullet
				enemyBullets[i]->resetObject();
				break;
			}
		}
	}
}



void SpriteManager::checkBunkerHitEnemy()
{
	// Check the Enemies bullets
	for (int i = 0; i < totalEnemyBullets; i++)
	{
		// Check an Enemy bullet is active
		if (enemyBullets[i]->isAlive() == true)
		{
			// select next Bunker
			for (int j = 0; j < totalBunkers; j++)
			{
				// see if Bunker is alive or not
				if (bunkers[j]->isAlive() == true)
				{
					// Bunker j vs enemyBullet i
					// Checks to see it the 2 objects are colliding
					if (collision_manager->checkCollision(bunkers[j]->getSizeX(),
						bunkers[j]->getSizeY(), bunkers[j]->getPosX(),
						bunkers[j]->getPosY(), enemyBullets[i]->getSizeX(),
						enemyBullets[i]->getSizeY(), enemyBullets[i]->getPosX(),
						enemyBullets[i]->getPosY()) == true)
					{
						// If bunker hit lower its life
						bunkers[j]->setLife();

						// PLay Bunker hit audio
						audio_manager->playAudio(sound_assets->bunkerHit);

						// destroy the bullet
						enemyBullets[i]->resetObject();
						break;
					}
				}
			}
		}
	}
}



void SpriteManager::spawnMotherShip()
{
	// MotherShip has random chance to spawn if not already alive
	int number;
	number = rand() % 1000;
	if (number < 1)
	{
		if (mother_ship->isAlive() == false)
		{
			mother_ship->resetPos();
			mother_ship->setAlive();
			// Play MotherShip Spawn audio
			audio_manager->playAudio(sound_assets->motherShip);
		}
	}
}



void SpriteManager::spawnEnemyBullet()
{
	// randomly select a column,
	// then select the highest enemy in the row
	// iterate backwards looking for an alive enemy in randomly chosed column
	int randColumn;
	int spawnBullet;
	randColumn = rand() % 11;
	spawnBullet = rand() % 1000;

	// Random chance to spawn an enemy bullet
	if (spawnBullet < 15)
	{
		// iterate through enemy bullets
		for (int i = 0; i < totalEnemyBullets; i++)
		{
			// check if Bullet is alive
			if (enemyBullets[i]->isAlive() == false)
			{
				// check enemys in reverse, to spawn bullet at the lowest
				// (on screen) enemy in randomly chosen column
				for (int j = (totalEnemies - 1); j >= 0; j--)
				{
					if (enemies[j]->isAlive() == true 
						&& enemies[j]->getColumn() == randColumn)
					{
						// Spawn bullet at enemy based on its size and pos
						enemyBullets[i]->spawnEnemyBullet(enemies[j]->
							getSprite(spriteSwitch)->position[0], enemies[j]->
							getSprite(spriteSwitch)->position[1],
								enemies[j]->getSprite(spriteSwitch)->size[0]);

						// play enemy fire audio
						audio_manager->playAudio(sound_assets->alienFire);
						return;
					}
				}
			}
		}
	}
}



int SpriteManager::getLives() const
{
	return player_one->getLives();
}



int SpriteManager::getScore() const
{
	return score;
}



int SpriteManager::getLevel() const
{
	return currentLevel;
}



bool SpriteManager::checkGameOver()
{
	for (int i = (totalEnemies - 1); i > -1; i--)
	{
		if (enemies[i]->isAlive() == true)
		{
			if (enemies[i]->getPosY() >= (height - 135))
			{
				audio_manager->playAudio(sound_assets->gameOver);
				return true;
			}
		}
	}
	return false;
}