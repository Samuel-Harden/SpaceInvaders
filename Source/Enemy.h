#pragma once

#include "Actor.h"

namespace ASGE {
	class Renderer;
	class Sprite;
}

class Enemy : public Actor
{
public:

	~Enemy();
	Enemy();

	ASGE::Sprite* getSprite(bool& _spriteSwitch) const;

	void tick() override;
	void moveLeft();
	void moveRight();
	void moveDown();

	int getRow() const;
	int getColumn() const;
	void setRow(int& _row);
	void setColumn(int& _column);

	void setPosX(int& _posX);
	void setPosY(int& _posY);
	void setSize(int& _sizeX, int& _sizeY);

	void loadSprite(std::shared_ptr<ASGE::Renderer>& renderer, const char*&
		_fileName1, const char*& _fileName2);

protected:

private:

	int row;
	int column;

};