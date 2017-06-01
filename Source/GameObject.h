#pragma once

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void tick();
protected:

private:

};