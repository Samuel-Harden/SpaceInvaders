#include "Bullet.h"



Bullet::Bullet()
{
	enemyBullet = false;
}



Bullet::~Bullet()
{

}



void Bullet::tick()
{

	// If the player fired this bullet
	if (alive == true && enemyBullet == false)
	{
		sprite1->position[1] -= 10;

		// Check bullet pos
		if (sprite1->position[1] < 70)
		{
			alive = false;
		}
	}

	// If an enemy fired this bullet
	if (alive == true && enemyBullet == true)
	{
		sprite1->position[1] += 5;

		// Check bullet pos
		if (sprite1->position[1] > 600)
		{
			alive = false;
		}
	}

	Actor::tick();
}



void Bullet::spawn(float _posX, float _posY, int _playerSize)
{
	alive = true;
	sprite1->position[0] = _posX + ((_playerSize / 2) - 3);
	sprite1->position[1] = _posY - 15;
}



void Bullet::spawnEnemyBullet(float _posX, float _posY, int _enemySize)
{
	alive = true;
	enemyBullet = true;
	sprite1->position[0] = _posX + ((_enemySize / 2) - 3);
	sprite1->position[1] = _posY + 15;
}



void Bullet::setSize(int& _sizeX, int& _sizeY)
{
	sprite1.get()->size[0] = _sizeX;
	sprite1.get()->size[1] = _sizeY;
}



void Bullet::reset()
{
	alive = false;
}