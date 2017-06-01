#pragma once

#include "Actor.h"

namespace ASGE {
	class Renderer;
	class Sprite;
}

class Bunker : public Actor
{
public:
	Bunker();
	~Bunker();

	void loadSprite(std::shared_ptr<ASGE::Renderer>& renderer, const char*&
		_fileName1, const char*& _fileName2, const char*& _flieName3);

	ASGE::Sprite* getSprite() const;

	void setPosX(int& _posX);
	void setPosY(int& _posY);
	void setSpriteNo(int& _spriteNo);
	void setSize(int& _sizeX, int& _sizeY);
	void setLife();
	void bunkerReset();

protected:

private:

	int spriteNo;

};