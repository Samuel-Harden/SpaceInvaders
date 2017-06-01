#include "MainMenu.h"
#include "Actions.h"
#include "Constants.h"
#include "GameFont.h"
#include "Game.h"

#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>

MainMenu::MainMenu()
{

}

MainMenu::~MainMenu()
{
	this->inputs->unregisterCallback(callback_id);
}

bool MainMenu::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	renderer->setWindowTitle("Invaders - Exercise 1");
	renderer->setClearColour(ASGE::COLOURS::BLACK);
	toggleFPS();

	// input callback function
	callback_id = this->inputs->addCallbackFnc(&MainMenu::input, this);

	// load fonts we need
	GameFont::fonts[0] = new GameFont(
		renderer->loadFont("..\\..\\Resources\\Fonts\\Comic.ttf", 42),
		"default", 42);

	

	if (GameFont::fonts[0]->id == -1)
	{
		return false;
	}

	return true;
}

bool MainMenu::run()
{
		while (!shouldExit())
		{
			processMenuActions();
			render();
		}

	return true;
}

bool MainMenu::shouldExit() const
{
	return (renderer->exit() || this->exit);
}

void MainMenu::render()
{
	beginFrame();
	drawFrame();
	endFrame();
}

void MainMenu::drawFrame()
{
	renderer->setFont(GameFont::fonts[0]->id);
	renderer->renderText
		("Space Invaders\n\nPlay Game _ ENTER\n\nHigh Sc0res"
			"_ SPACE\n\nExit Game _ ESC",
		(width/2), (height/2), 1.0, ASGE::COLOURS::BLUEVIOLET);
}

void MainMenu::input(int key, int action) const
{
	if (action == ASGE::KEYS::KEY_PRESS)
	{
		if (key == ASGE::KEYS::KEY_ESCAPE)
		{
			game_action = GameAction::EXIT;
		}
	}
}

void MainMenu::processMenuActions()
{
	if (game_action == GameAction::EXIT)
	{
		this->exit = true;
	}

	game_action = GameAction::NONE;
}

int MainMenu::newGame()
{
	InvadersGame invaderGame;

	if (invaderGame.init())
	{
		return invaderGame.run();
	}

	// game failed to initialise
	else
	{
		return -1;
	}
}