#include "EnemyManager.h"
#include "Actions.h"

EnemyManager::EnemyManager(int _totalEnemies)
{
	enemies.reserve(_totalEnemies);
	counter = 0;
	spriteSwitch = true;
	moveLeft = false;
	moveRight = true;
	moveDown = false;
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::generateEnemies(std::shared_ptr<ASGE::Renderer> renderer, int _totalEnemies)
{
	totalEnemies = _totalEnemies;
	int counter = 0;
	int alienType = 0;
	int ensizeX = 24;
	int ensizeY = 16;
	int posX = 300;
	int posY = 100;
	alien1a = "..\\..\\Resources\\Textures\\Top_Alien_1.png";
	alien1b = "..\\..\\Resources\\Textures\\Top_Alien_2.png";
	alien2a = "..\\..\\Resources\\Textures\\Mid_Alien_1.png";
	alien2b = "..\\..\\Resources\\Textures\\Mid_Alien_2.png";
	alien3a = "..\\..\\Resources\\Textures\\Bot_Alien_1.png";
	alien3b = "..\\..\\Resources\\Textures\\Bot_Alien_2.png";

	// Create the aliens
	for (int i = 0; i < totalEnemies; i++)
	{
		alien = new Enemy;
		if (alienType == 0 || alienType == 3)
		{
			alien->loadSprite(renderer, alien1a, alien1b);
		}
		if (alienType == 1 || alienType == 4)
		{
			alien->loadSprite(renderer, alien2a, alien2b);
		}
		if (alienType == 2)
		{
			alien->loadSprite(renderer, alien3a, alien3b);
		}
		alien->setSize(ensizeX, ensizeY);
		alien->setPosX(posX);
		alien->setPosY(posY);
		posX += 36;

		enemies.push_back(alien);

		counter++;
		if (counter == 11)
		{
			posX = 300;
			posY += 36;
			counter = 0;
			alienType++;
		}
	}
}

void EnemyManager::renderEnemies(std::shared_ptr<ASGE::Renderer> renderer)
{
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->getSprite(spriteSwitch)->render(renderer);
	}
}

void EnemyManager::updateEnemyPositions()
{
	// change sprite each time they move
	changeSprite();

	if (enemy_state == EnemyState::RIGHT)
	{
		moveEnemiesRight();
		if (counter == 6)
		{
			enemy_state = EnemyState::DOWN;
			counter = 0;
		}
		counter++;
		return;
	}
	if (enemy_state == EnemyState::LEFT)
	{
		moveEnemiesLeft();
		if (counter == 6)
		{
			enemy_state = EnemyState::DOWN;
			counter = 0;
		}
		counter++;
		return;
	}
	
	if (enemy_state == EnemyState::DOWN)
	{
		moveEnemiesDown();
		if (counter == 1)
		{
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
}

void EnemyManager::moveEnemiesRight()
{
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->moveRight();
	}
}

void EnemyManager::moveEnemiesLeft()
{
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->moveLeft();
	}
}

void EnemyManager::moveEnemiesDown()
{
	for (int i = 0; i < totalEnemies; i++)
	{
		enemies[i]->moveDown();
	}
}

void EnemyManager::changeSprite()
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