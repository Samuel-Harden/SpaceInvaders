#pragma once

#include <Engine/OGLGame.h>
#include <memory>
#include <string>

// Declarations
struct GameFont;
class SpriteManager;

/**
*  Invaders Game. An OpenGL Game based on ASGE.
*/

class InvadersGame:
	public ASGE::OGLGame
{
public:
	InvadersGame();
	~InvadersGame();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;
	void render();

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();

private:
	void processGameActions(); 
	void input(int key, int action) const;
	void setWindowName(const char* name) const;
	void displayMenu() const;
	void displayGame();
	void displayPause() const;
	void displayScore();
	void displayGameOver();
	void displayLevelComplete();
	void checkGameState();
	void checkGameAction() const;
	void checkFireState() const;
	void resetDifficulty();
	void increaseDifficulty();

	bool tick();
	bool setFonts();

	int  callback_id = -1;		/**< Input Callback ID. The callback ID assigned by the game engine. */
	bool exit = false;          /**< Exit boolean. If true the game loop will exit. */

	int totalEnemies;
	int totalEnemyBullets;
	int totalBunkers;
	int updateCounter;
	int pauseCounter;
	int difficulty;
	bool difficultyUpdated;

	std::string score;
	std::string lives;
	std::string level;

	std::unique_ptr<SpriteManager> spriteManager = nullptr;
};

