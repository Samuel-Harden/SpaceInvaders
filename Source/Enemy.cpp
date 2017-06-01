#include <Engine/Renderer.h>

#include "Enemy.h"



Enemy::Enemy()
{
	alive = true;
}



Enemy::~Enemy()
{

}



void Enemy::loadSprite(std::shared_ptr<ASGE::Renderer>& renderer, const char*&
	_fileName1, const char*& _fileName2)
{
	sprite1 = renderer->createSprite();
	sprite1->loadTexture(_fileName1);
	sprite1->position[0] = 0;
	sprite1->position[1] = 0;

	sprite2 = renderer->createSprite();
	sprite2->loadTexture(_fileName2);
	sprite2->position[0] = 0;
	sprite2->position[1] = 0;
}



ASGE::Sprite* Enemy::getSprite(bool& _spriteSwitch) const
{
	if (_spriteSwitch == true)
	{
	return sprite1.get();
	}

	if (_spriteSwitch == false)
	{
	return sprite2.get();
	}
}



void Enemy::tick()
{
	Actor::tick();
}



void Enemy::moveRight()
{
	sprite1->position[0] += 36;
	sprite2->position[0] += 36;
}



void Enemy::moveLeft()
{
	sprite1->position[0] -= 36;
	sprite2->position[0] -= 36;
}



void Enemy::moveDown()
{
	sprite1->position[1] += 36;
	sprite2->position[1] += 36;
}



void Enemy::setPosX(int& _posX)
{
	sprite1.get()->position[0] = _posX;
	sprite2.get()->position[0] = _posX;
}



void Enemy::setPosY(int& _posY)
{
	sprite1.get()->position[1] = _posY;
	sprite2.get()->position[1] = _posY;
}



void Enemy::setSize(int& _sizeX, int& _sizeY)
{
	sprite1.get()->size[0] = _sizeX;
	sprite1.get()->size[1] = _sizeY;

	sprite2.get()->size[0] = _sizeX;
	sprite2.get()->size[1] = _sizeY;
}



void Enemy::setRow(int& _row)
{
	row = _row;
}



void Enemy::setColumn(int& _column)
{
	column = _column;
}



int Enemy::getRow() const
{
	return row;
}



int Enemy::getColumn() const
{
	return column;
}
