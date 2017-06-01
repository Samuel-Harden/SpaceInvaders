#include <Engine/Renderer.h>

#include "Actor.h"



void Actor::loadSprite(std::shared_ptr<ASGE::Renderer>& renderer,
	const char*& _fileName1)
{
	sprite1 = renderer->createSprite();
	sprite1->loadTexture(_fileName1);
	sprite1->position[0] = 0;
	sprite1->position[1] = 0;
}



ASGE::Sprite* Actor::getSprite() const
{
	return sprite1.get();
}



bool Actor::isAlive() const
{
	return alive;
}



void Actor::setPosX(int& _posX)
{
	sprite1.get()->position[0] = _posX;
}



void Actor::setPosY(int& _posY)
{
	sprite1.get()->position[1] = _posY;
}



void Actor::setSize(int& _sizeX, int& _sizeY)
{
	sprite1.get()->size[0] = _sizeX;
	sprite1.get()->size[1] = _sizeY;
}



float Actor::getPosX() const
{
	return sprite1.get()->position[0];
}



float Actor::getPosY() const
{
	return sprite1.get()->position[1];
}



float Actor::getSizeX() const
{
	return sprite1.get()->size[0];
}



float Actor::getSizeY() const
{
	return sprite1.get()->size[1];
}



void Actor::tick()
{
	
}



void Actor::resetObject()
{
	alive = false;
}



void Actor::setAlive()
{
	alive = true;
}



void Actor::setGameDimentions(int& _width, int& _height)
{
	width = _width;
	height = _height;
}