#pragma once
#include "GameObject.h"
class Barrier : public GameObject
{
private :
	bool m_movingRight = true;

public:

	Barrier();
	Barrier(int xPos, int yPos, char body, bool isMovingright);
	virtual void update() override;

};

