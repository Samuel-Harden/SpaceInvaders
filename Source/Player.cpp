#include "Player.h"



Player::Player()
{
	lives = 3;
}



Player::~Player() 
{

}



void Player::tick()
{

	Actor::tick();
}



void Player::moveLeft()
{
	sprite1.get()->position[0] -= 3;
	setMaxPosX();
}



void Player::moveRight()
{
	sprite1.get()->position[0] += 3;
	setMaxPosX();
}



void Player::fire()
{

}



void Player::resetPos() const
{
	sprite1->position[0] = ((width / 2 - (sprite1->size[0] / 2)));
	sprite1->position[1] = height - 100;
}



void Player::setSize(int& _sizeX, int& _sizeY)
{
	sprite1.get()->size[0] = _sizeX;
	sprite1.get()->size[1] = _sizeY;
}



void Player::setMaxPosX()
{
	if (sprite1->position[0] <= 10)
	{
		sprite1->position[0] = 11;
	}

	if (sprite1->position[0] >= ((width - 10) - (sprite1->size[0])))
	{
		sprite1->position[0] = ((width - 11) - (sprite1->size[0]));
	}
}



void Player::resetLives()
{
	lives = 3;
}



int Player::getLives() const
{
	return lives;
}



void Player::playerHit()
{
	lives -= 1;
	resetPos();
}



void Player::addLife()
{
	lives += 1;
}