#include <Engine/Renderer.h>

#include "MotherShip.h"



MotherShip::MotherShip()
{
	alive = false;
}



MotherShip::~MotherShip()
{

}



void MotherShip::tick()
{
	sprite1.get()->position[0] -= 2;

	if (sprite1.get()->position[0] < 20)
	{
		alive = false;
	}
	Actor::tick();
}



void MotherShip::setPosX(int& _posX)
{
	sprite1.get()->position[0] = _posX;
}



void MotherShip::setPosY(int& _posY)
{
	sprite1.get()->position[1] = _posY;
}



void MotherShip::setSize(int& _sizeX, int& _sizeY)
{
	sprite1.get()->size[0] = _sizeX;
	sprite1.get()->size[1] = _sizeY;
}



void MotherShip::resetPos() const
{
	sprite1->position[0] = ((width - 20) - (sprite1->size[0]));
	sprite1->position[1] = 75;
}
