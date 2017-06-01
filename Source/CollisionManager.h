#pragma once

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	// Takes parameters for 2 objects, and checks their respective
	// sizes and positions against each other
	bool checkCollision(float object1SizeX, float object1SizeY,
		float object1PosX, float object1PosY,
		float object2Size, float object2SizeY,
		float object2PosX, float object2PosY);

protected:

private:
};