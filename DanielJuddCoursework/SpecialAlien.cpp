#include "SpecialAlien.h"


//move special alein on update if it is active
void SpecialAlien::update(float deltaTime)
{
	if(!m_isActive)
	{
		return;
	}


	m_moveDelta += deltaTime;
	if (m_moveDelta >= m_moveDelay)
	{
		move(1, 0);
		m_moveDelta = 0.0f;
		if(m_position.x > 80)
		{
			m_isActive = false;
		}
	}
}

//spawns in the special alien
void SpecialAlien::spawn(Vector2 pos)
{
	m_position = pos;
	m_isActive = true;
	m_moveDelta = 0.0f;
}





