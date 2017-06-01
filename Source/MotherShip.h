#pragma once

#include "Actor.h"

namespace ASGE {
	class Renderer;
	class Sprite;
}

class MotherShip : public Actor
{
public:

	~MotherShip();
	MotherShip();

	void tick() override;

	void setPosX(int& _posX);
	void setPosY(int& _posY);
	void setSize(int& _sizeX, int& _sizeY);
	void resetPos() const;

protected:

private:

};