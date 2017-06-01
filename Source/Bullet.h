#pragma once

#include "Actor.h"

namespace ASGE {
	class Renderer;
	class Sprite;
}

class Bullet : public Actor
{
public:
	Bullet();
	~Bullet();

	void tick() override;
	void spawn(float _posX, float _posY, int _playerSize);
	void spawnEnemyBullet(float _posX, float _posY, int _enemySize);
	void setSize(int& _sizeX, int& _sizeY) override;
	void reset();
protected:

private:

	bool enemyBullet;

};