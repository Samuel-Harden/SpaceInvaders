#pragma once

#include "Enemy.h"
#include <vector>

class EnemyManager
{
public:
	EnemyManager(int _totalEnemies);
	~EnemyManager();

	void generateEnemies(std::shared_ptr<ASGE::Renderer> renderer, int _totalEnemies);
	void renderEnemies(std::shared_ptr<ASGE::Renderer> renderer);
	void updateEnemyPositions();
	void moveEnemiesRight();
	void moveEnemiesLeft();
	void moveEnemiesDown();

protected:

private:

	void changeSprite();
	int totalEnemies;

	std::vector<Enemy*> enemies;
	Enemy* alien;

	const char* alien1a;
	const char* alien1b;
	const char* alien2a;
	const char* alien2b;
	const char* alien3a;
	const char* alien3b;

	bool spriteSwitch;
	bool moveRight;
	bool moveLeft;
	bool moveDown;
	int counter;
};