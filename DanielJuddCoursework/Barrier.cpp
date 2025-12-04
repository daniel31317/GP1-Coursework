#include "Barrier.h"

Barrier::Barrier() : GameObject()
{
	
}
Barrier::Barrier(int xPos, int yPos, char body, bool isMovingright) : GameObject(xPos, yPos, body), m_movingRight(isMovingright)
{
	
}

Barrier::Barrier(Vector2 pos, char body, bool isMovingright) : GameObject(pos, body), m_movingRight(isMovingright)
{

}

void Barrier::damageBarrier()
{
	if (m_barrierHealth == 0)
	{
		return;
	}
	m_barrierHealth--;
	m_body = m_barrierStates[m_barrierHealth];
}

void Barrier::update()
{
	if (m_movingRight)
	{
		if (m_position.x < 79)
		{
			move(1, 0);
		}
		else
		{
			m_movingRight = !m_movingRight;
		}
	}
	else
	{
		if (m_position.x > 0)
		{
			move(-1, 0);
		}
		else
		{
			m_movingRight = !m_movingRight;
		}
	}
}


