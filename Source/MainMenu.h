#pragma once
#include <Engine/OGLGame.h>

class Game;
struct GameFont;

class MainMenu:
	public ASGE::OGLGame
{
public:

	MainMenu();
	~MainMenu();

	// Inherited via Game
	virtual bool run() override;
	bool shouldExit() const;
	void render();
	
	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();

protected:

private:
	void processMenuActions();
	void input(int key, int action) const;

	/**< Input Callback ID. The callback ID assigned by the game engine. */
	int  callback_id = -1;
	/**< Exit boolean. If true the game loop will exit. */
	bool exit = false;

	int newGame();

	//InvadersGame* invaderGame;
	//std::unique_ptr<InvadersGame> invaderGame = nullptr;

};