#include <Engine/Renderer.h>

#include "Bunker.h"



Bunker::Bunker()
{
	spriteNo = 0;
	alive = true;
}



Bunker::~Bunker()
{

}



void Bunker::loadSprite(std::shared_ptr<ASGE::Renderer>& renderer, const char*&
	_fileName1, const char*& _fileName2, const char*& _fileName3)
{
	sprite1 = renderer->createSprite();
	sprite1->loadTexture(_fileName1);
	sprite1->position[0] = 0;
	sprite1->position[1] = 0;

	sprite2 = renderer->createSprite();
	sprite2->loadTexture(_fileName2);
	sprite2->position[0] = 0;
	sprite2->position[1] = 0;

	sprite3 = renderer->createSprite();
	sprite3->loadTexture(_fileName3);
	sprite3->position[0] = 0;
	sprite3->position[1] = 0;
}



ASGE::Sprite* Bunker::getSprite() const
{
	if (spriteNo == 0)
	{
		return sprite1.get();
	}

	if (spriteNo == 1)
	{
		return sprite2.get();
	}

	if (spriteNo == 2)
	{
		return sprite3.get();
	}
}



void Bunker::setPosX(int& _posX)
{
	sprite1.get()->position[0] = _posX;
	sprite2.get()->position[0] = _posX;
	sprite3.get()->position[0] = _posX;
}



void Bunker::setPosY(int& _posY)
{
	sprite1.get()->position[1] = _posY;
	sprite2.get()->position[1] = _posY;
	sprite3.get()->position[1] = _posY;
}



void Bunker::setSize(int& _sizeX, int& _sizeY)
{
	sprite1.get()->size[0] = _sizeX;
	sprite1.get()->size[1] = _sizeY;

	sprite2.get()->size[0] = _sizeX;
	sprite2.get()->size[1] = _sizeY;

	sprite3.get()->size[0] = _sizeX;
	sprite3.get()->size[1] = _sizeY;
}



void Bunker::setSpriteNo(int& _spriteNo)
{
	spriteNo = _spriteNo;
}



void Bunker::setLife()
{
	if (spriteNo == 0)
	{
		spriteNo = 1;
		return;
	}

	if (spriteNo == 1)
	{
		spriteNo = 2;
		return;
	}

	if (spriteNo == 2)
	{
		resetObject();
		return;
	}
}



void Bunker::bunkerReset()
{
	spriteNo = 0;

	if (alive == false)
	{
		alive = true;
	}
}