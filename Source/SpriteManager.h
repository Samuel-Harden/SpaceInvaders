#pragma once

#include <vector>
#include "AudioManager.h"
#include <Engine/Sprite.h>

class Enemy;
class Player;
class Bullet;
class MotherShip;
class Bunker;

class SoundAssets;
class SpriteAssets;
class CollisionManager;

class SpriteManager
{
public:
	SpriteManager(int& _totalEnemies, int& _totalBunkers, int& _totalEnemyBullets, int& _width, int& _height);
	~SpriteManager();

	void generateGameObjects(std::shared_ptr<ASGE::Renderer>& renderer, int& _totalEnemies, int& _totalBunkers);
	void renderEnemies(std::shared_ptr<ASGE::Renderer>& renderer);
	void renderBunkers(std::shared_ptr<ASGE::Renderer>& renderer);
	void renderPlayer(std::shared_ptr<ASGE::Renderer>& renderer) const;
	void renderMotherShip(std::shared_ptr<ASGE::Renderer>& renderer) const;
	void renderBullets(std::shared_ptr<ASGE::Renderer>& renderer);
	void renderEnemyBullets(std::shared_ptr<ASGE::Renderer>& renderer);
	void updateEnemyPositions(int& width, int& height);
	void update();
	void resetGameObjects();
	void resetScore();
	void resetLevelWon();
	void resetPlayerLives();
	void resetCurrentLevel();
	void movePlayerLeft() const;
	void movePlayerRight() const;
	void firePlayerBullet();

	bool checkGameOver();

	int getLives() const;
	int getScore() const;
	int getLevel() const;

	bool playerBulletAlive();
	bool motherShipAlive();

	std::unique_ptr<AudioManager> audio_manager = nullptr;

protected:

private:

	// Internal functions
	
	// construction functions
	void generateEnemies(std::shared_ptr<ASGE::Renderer>& renderer,
		int _totalEnemies);
	void generateBunkers(std::shared_ptr<ASGE::Renderer>& renderer,
		int _totalBunkers);
	void generatePlayer(std::shared_ptr<ASGE::Renderer>& renderer);
	void generateBullet(std::shared_ptr<ASGE::Renderer>& renderer);
	void generateEnemyBullets(std::shared_ptr<ASGE::Renderer>& renderer);
	void generateMotherShip(std::shared_ptr<ASGE::Renderer>& renderer);


	void moveEnemiesRight() const;
	void moveEnemiesLeft() const;
	void moveEnemiesDown() const;
	void checkEnemyHit();
	void checkMotherShipHit();
	void checkBunkerHitPlayer();
	void checkBunkerHitEnemy();
	void checkPlayerHit();
	void changeSprite();
	void spawnMotherShip();
	void spawnEnemyBullet();

	int totalEnemies;
	int totalBunkers;
	int totalEnemyBullets;
	int bunkerLv;
	int score;
	int currentLevel;
	int deadEnemies;

	std::vector<Enemy*> enemies;
	Enemy* alien;

	std::vector<Bullet*> enemyBullets;
	Bullet* enemy_bullet;

	std::vector<Bunker*> bunkers;
	Bunker* bunker;

	std::unique_ptr<Player> player_one = nullptr;
	std::unique_ptr<Bullet> player_bullet = nullptr;
	std::unique_ptr<MotherShip> mother_ship = nullptr;

	std::unique_ptr<SoundAssets> sound_assets = nullptr;
	std::unique_ptr<SpriteAssets> sprite_assets = nullptr;
	std::unique_ptr<CollisionManager> collision_manager = nullptr;

	bool spriteSwitch;
	bool moveRight;
	bool moveLeft;
	bool moveDown;
	int counter;
	int width;
	int height;

};