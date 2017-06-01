#pragma once

#include "Actor.h"

namespace ASGE {
	class Renderer;
	class Sprite;
}

class Player : public Actor
{
public:
	~Player();
	Player();

	void tick() override;
	void resetPos() const;
	void moveLeft();
	void moveRight();
	void fire();
	void resetLives();
	void playerHit();
	int getLives() const;
	void addLife();
	void setSize(int& _sizeX, int& _sizeY) override;

protected:

private:
	void setMaxPosX();
	int lives;
};