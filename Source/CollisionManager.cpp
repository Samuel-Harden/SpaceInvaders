#include "CollisionManager.h"



CollisionManager::CollisionManager()
{

}



CollisionManager::~CollisionManager()
{

}



// Checksto see if the two objects overlap,
// if so return true, if not return false
bool CollisionManager::checkCollision(float object1SizeX, float object1SizeY,
	float object1PosX, float object1PosY,
	float object2SizeX, float object2SizeY,
	float object2PosX, float object2PosY)
{
	// ((A.X + A.Width) >= (B.X) &&
	if ((object1PosX + object1SizeX)
		>= (object2PosX) &&
		// (A.X) <= (B.X + B.Width) &&
		(object1PosX) <= (object2PosX
			+ object2SizeX) &&

		// (A.Y + A.Height) >= (B.Y) &&
		(object1PosY + object1SizeY)
		>= (object2PosY) &&
		// (A.Y) <= (B.Y + B.Height))
		(object1PosY) <= (object2PosY
			+ object2SizeY))
	{
		return true;
	}
	else
		return false;
}