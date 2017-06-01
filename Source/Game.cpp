#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

#include <iostream>
#include <sstream>

#include "Game.h"

#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "SpriteManager.h"



/**
*   @brief   Default Constructor.
*/
InvadersGame::InvadersGame()
{

}



/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
InvadersGame::~InvadersGame()
{
	this->inputs->unregisterCallback(callback_id);
}



/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The input callback should also
			 be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool InvadersGame::init()
{
	//width = WINDOW_WIDTH;
	//height = WINDOW_HEIGHT;
	width = 800;
	height = 600;


	//Set Variables
	totalEnemies = 55;
	totalEnemyBullets = 5;
	totalBunkers = 4;
	updateCounter = 0;
	difficulty = 100;
	bool difficultyUpdated;

	if (!initAPI())
	{
		return false;
	}

	setWindowName("invaders - Exersise 1");
	toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(&InvadersGame::input, this);

	setFonts();

	// Create the manager responsible for all 
	// game objects (Player, Bullets, Enemies...)
	spriteManager = std::make_unique<SpriteManager>(totalEnemies, totalBunkers,
		totalEnemyBullets, width, height);

	//Generate Game Objects
	spriteManager->generateGameObjects(renderer, totalEnemies, totalBunkers);

	// Set initial game state and action
	game_state = GameState::MENU;
	player_action = PlayerAction::NONE;
	fire_state = FireState::NONE;
	enemy_state = EnemyState::RIGHT;

	return true;
}



/**
*   @brief   The main game loop.
*   @details The main loop should be responsible for updating the game
			 and rendering the current scene. Runs until the shouldExit
			 signal is received.
*   @return  True if the game ran correctly.
*/
bool InvadersGame::run()
{
	while (!shouldExit())
	{
		processGameActions();
		render();
		tick();
		spriteManager->audio_manager->tick();
	}

	return true;
}



bool InvadersGame::tick()
{
	//update all objects
	if (game_state == GameState::PLAY)
	{
		spriteManager->update();

		if (updateCounter >= difficulty)
		{
			spriteManager->updateEnemyPositions(width, height);
			updateCounter = 0;
		}
		checkGameAction();
		checkFireState();
		if (spriteManager->checkGameOver() == true)
		{
			game_state = GameState::GAME_OVER;
		}
		updateCounter++;
	}

	return true;
}



/**
*   @brief   Should the game exit?
*   @details Has the renderer terminated or the game requesting to exit?
*   @return  True if the game should exit
*/
bool InvadersGame::shouldExit() const
{
	return (renderer->exit() || this->exit);
}



/**
*   @brief   Renders the scene
*   @details Prepares the renderer subsystem before drawing the
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void InvadersGame::render()
{
	beginFrame();
	drawFrame();
	endFrame();
}



/**
*   @brief   Renderers the contents for this frame
*   @details All game objects that need rendering should be done
			 in this function, as it ensures they are completed
			 before the buffers are swapped.
*   @return  void
*/
void InvadersGame::drawFrame()
{
	switch (game_state)
	{
	case GameState::MENU:
	{
		resetDifficulty();
		displayMenu();
		break;
	}
	case GameState::PLAY:
	{
		if (difficultyUpdated == true)
		{
			difficultyUpdated = false;
		}

		// check no of lives left
		if (spriteManager->getLives() > 0)
		{
			displayGame();
			break;
		}

		else
			game_state = GameState::GAME_OVER;
			player_action = PlayerAction::NONE;
	}
	case GameState::GAME_OVER:
	{
		displayGameOver();
		break;
	}
	case GameState::LEVEL_WON:
	{
		if (difficultyUpdated == false)
		{
			increaseDifficulty();
		}
		displayLevelComplete();
		break;
	}
	case GameState::PAUSE:
	{
		displayPause();
		break;
	}
	}
}



/**
*   @brief   Processes any key inputs and translates them to a GameAction
*   @details This function is added as a callback to handle the game's
			 input. Key presseses are translated in to GameActions which
			 are then processed by the main game loop.
*   @param   key is the key the action relates to
*   @param   action whether the key was released or pressed
*   @return  void
*/
void InvadersGame::input(int key, int action) const
{
	//Main Menu Actions
	if (game_state == GameState::MENU)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE && action == ASGE::KEYS::KEY_PRESSED)
		{
			game_state = GameState::EXIT;
		}

		if (key == ASGE::KEYS::KEY_ENTER)
		{
			game_state = GameState::PLAY;
		}
	}

	// Pause Menu Actions
	if (game_state == GameState::PAUSE)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE && action == ASGE::KEYS::KEY_PRESSED)
		{
			game_state = GameState::MENU;
		}

		if (key == ASGE::KEYS::KEY_P && action == ASGE::KEYS::KEY_PRESSED)
		{
			game_state = GameState::PLAY;
			player_action = PlayerAction::NONE;
			return;
		}
	}

	// In Game Controls
	if (game_state == GameState::PLAY)
	{
		// Move Left
		if (key == ASGE::KEYS::KEY_A && action == ASGE::KEYS::KEY_PRESSED)
		{
			player_action = PlayerAction::LEFT;
		}

		// Move Right
		if ((key == ASGE::KEYS::KEY_D) && (action == ASGE::KEYS::KEY_PRESSED))
		{
			player_action = PlayerAction::RIGHT;
		}

		// Left Released
		if (key == ASGE::KEYS::KEY_A && action == ASGE::KEYS::KEY_RELEASED)
		{
			if (player_action != PlayerAction::RIGHT)
			{
				player_action = PlayerAction::NONE;
			}
		}

		// Right Released
		if (key == ASGE::KEYS::KEY_D && action == ASGE::KEYS::KEY_RELEASED)
		{
			if (player_action != PlayerAction::LEFT)
			{
				player_action = PlayerAction::NONE;
			}
		}

		// If Space bar is pressed Fire a bullet
		if (key == ASGE::KEYS::KEY_SPACE && action == ASGE::KEYS::KEY_PRESSED)
		{
			fire_state = FireState::FIRE;

			if (spriteManager->playerBulletAlive() == true)
			{
				fire_state = FireState::NONE;
			}
		}

		// Pause State
		if (key == ASGE::KEYS::KEY_P && action == ASGE::KEYS::KEY_PRESSED)
		{
			game_state = GameState::PAUSE;
			player_action = PlayerAction::NONE;
			return;
		}
	}

	//LevelWon State
	if (game_state == GameState::LEVEL_WON)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE && action == ASGE::KEYS::KEY_PRESSED)
		{
			game_state = GameState::MENU;
			return;
		}

		if (key == ASGE::KEYS::KEY_ENTER && action == ASGE::KEYS::KEY_PRESSED)
		{
			player_action = PlayerAction::NONE;
			spriteManager->resetGameObjects();
			spriteManager->resetLevelWon();
			game_state = GameState::PLAY;
			return;
		}
	}
	
	// GameOver State
	if (game_state == GameState::GAME_OVER)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE && action == ASGE::KEYS::KEY_PRESSED)
		{
			game_state = GameState::MENU;
			return;
		}
	}
}



/**
*   @brief   Processes the next game action
*   @details Uses the game action that was a direct result of 
*            user input. It allows input to processed in a different
             thread and the game actions performed in the main thread. 
*   @return  void
*/
void InvadersGame::processGameActions()
{
	checkGameState();
}



void InvadersGame::setWindowName(const char* name) const
{
	renderer->setWindowTitle(name);
	renderer->setClearColour(ASGE::COLOURS::BLACK);
}



bool InvadersGame::setFonts()
{
	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42),
		"default", 42);

	renderer->setFont(GameFont::fonts[0]->id);

	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	return true;
}



void InvadersGame::displayMenu() const
{
	renderer->renderText
		("SPACE INVADERS\n\nNEW GAME - ENTER\n\nQUIT GAME - ESC",
		375, 325, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("BY SAMUEL HARDEN",
		990, 680, 0.75, ASGE::COLOURS::WHITE);
}



void InvadersGame::displayGame()
{
	displayScore();

	spriteManager->renderPlayer(renderer);
	
	spriteManager->renderEnemies(renderer);

	spriteManager->renderBunkers(renderer);

	spriteManager->renderEnemyBullets(renderer);

	// Check to see if we actually need to render objects
	if (spriteManager->playerBulletAlive() == true)
	{
		spriteManager->renderBullets(renderer);
	}

	if (spriteManager->motherShipAlive() == true)
	{
		spriteManager->renderMotherShip(renderer);
	}
}



void InvadersGame::displayPause() const
{
	renderer->renderText("GAME PAUSED",
		100, 150, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("CURRENT SCORE: ",
		100, 300, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText((score.c_str()),
		450, 300, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("NUMBER OF LIVES: ",
		100, 450, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText((lives.c_str()),
		450, 450, 1.0, ASGE::COLOURS::WHITE);

	renderer->renderText("P - UNPAUSE   ESC - RETURN TO MAIN MENU",
		100, 600, 1.0, ASGE::COLOURS::RED);
}



void InvadersGame::displayLevelComplete()
{

	score = std::to_string(spriteManager->getScore());

	renderer->renderText("LEVEL COMPLETE",
		100, 150, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("CURRENT SCORE: ",
		100, 300, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText((score.c_str()),
		450, 300, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("NUMBER OF LIVES: ",
		100, 450, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText((lives.c_str()),
		450, 450, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText(" ( +1 EXTRA LIFE) ",
		550, 450, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("ENTER - PLAY NEXT LEVEL   ESC - RETURN TO MAIN MENU",
		100, 600, 1.0, ASGE::COLOURS::RED);
}



void InvadersGame::displayGameOver()
{
	score = std::to_string(spriteManager->getScore());

	lives = std::to_string(spriteManager->getLives());

	renderer->renderText("GAMEOVER",
		100, 150, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("SCORE: ",
		100, 300, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText((score.c_str()),
		250, 300, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("ESC - RETURN TO MAIN MENU",
		100, 450, 1.0, ASGE::COLOURS::RED);
}



void InvadersGame::checkGameState()
{
	switch (game_state)
	{
		case GameState::EXIT:
		{
			this->exit = true;
			break;
		}

		case GameState::PLAY:
		{
			displayGame();
			break;
		}

		case GameState::MENU:
		{

			// When player goes back to menu, reset game
			spriteManager->resetGameObjects();
			spriteManager->resetPlayerLives();
			spriteManager->resetScore();
			spriteManager->resetCurrentLevel();
			spriteManager->resetLevelWon();
			displayMenu();
			break;
		}

		case GameState::PAUSE:
		{
			displayPause();
			break;
		}
	}
}



void InvadersGame::checkGameAction() const
{
	switch (player_action)
	{
		case PlayerAction::LEFT:
		{
			spriteManager->movePlayerLeft();
			break;
		}

		case PlayerAction::RIGHT:
		{
			spriteManager->movePlayerRight();
			break;
		}
	}
}



void InvadersGame::checkFireState() const
{
	if(fire_state == FireState::FIRE)
	{
		if (spriteManager->playerBulletAlive() == false)
		{
			spriteManager->firePlayerBullet();
			fire_state = FireState::NONE;
		}
	}
}



void InvadersGame::displayScore()
{
	score = std::to_string(spriteManager->getScore());

	lives = std::to_string(spriteManager->getLives());

	level = std::to_string(spriteManager->getLevel());

	renderer->renderText("LEVEL: ",
		500, 50, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText(level.c_str(),
		625, 50, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText(("SCORE: "),
		875, 50, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText(score.c_str(),
		1020, 50, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("NO. OF LIVES: ",
		75, 50, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText(lives.c_str(),
		325, 50, 1.0, ASGE::COLOURS::WHITE);
	renderer->renderText("A - MOVE LEFT",
		75, 700, 0.5, ASGE::COLOURS::RED);
	renderer->renderText("d - MOVE RIGHT",
		225, 700, 0.5, ASGE::COLOURS::RED);
	renderer->renderText("SPACE - FIRE",
		400, 700, 0.5, ASGE::COLOURS::RED);
	renderer->renderText("P - PAUSE",
		550, 700, 0.5, ASGE::COLOURS::RED);
}



// After each wave is completed, 
// decrease time between enemies updating positions
void InvadersGame::increaseDifficulty()
{
	difficulty -= 10;
	difficultyUpdated = true;
}



void InvadersGame::resetDifficulty()
{
	difficulty = 100;
}