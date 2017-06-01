#pragma once

#include <Engine/Sprite.h>

class Actor
{
public:
	Actor() = default;
	~Actor() = default;

	ASGE::Sprite* getSprite() const;

	bool isAlive() const;
	void setPosX(int& _posX);
	void setPosY(int& _posY);

	float getPosX() const;
	float getPosY() const;

	float getSizeX() const;
	float getSizeY() const;

	virtual void setSize(int& _sizeX, int& _sizeY);

	void resetObject();
	void setAlive();
	void setGameDimentions(int& _width, int& _height);

	void loadSprite(std::shared_ptr<ASGE::Renderer>& renderer,
		const char*& _fileName);

	virtual void tick();
protected:
	bool alive;
	std::unique_ptr<ASGE::Sprite> sprite1;
	std::unique_ptr<ASGE::Sprite> sprite2;
	std::unique_ptr<ASGE::Sprite> sprite3;

	int height;
	int width;

private:
};