#pragma once
#include "GameObject.h"
class Barrier : public GameObject
{
private :
	bool m_movingRight = true;
	char m_barrierStates[4] = { ' ', '-', '+', '#' };
	int m_barrierHealth = 3;
public:

	Barrier();
	Barrier(int xPos, int yPos, char body, bool isMovingright);
	Barrier(Vector2 pos, char body, bool isMovingright);
	void damageBarrier();
	int getBarrierHealth() const { return m_barrierHealth; }
	bool isActive() { return m_barrierHealth == 0; }
	virtual void update() override;

};

