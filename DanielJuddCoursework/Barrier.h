#pragma once
#include "GameObject.h"
class Barrier : public GameObject
{
private :
	bool m_movingRight = true;

public:

	Barrier();
	Barrier(int xPos, int yPos, char body, bool isMovingright);
	Barrier(Vector2 pos, char body, bool isMovingright);
	virtual void update() override;

};

