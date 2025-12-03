#include "Missile.h"

void Missile::update()
{
	if (m_isActive)
	{
		move(0, -1);
	}
	if (m_position.y < 0)
	{
		m_isActive = false;
	}
}
void Missile::fireMissile(Vector2 pos)
{
	//if missile is already active return if not set position and make it active
	if (m_isActive)
	{
		return;
	}

	m_position = pos;
	m_position.y--;
	m_isActive = true;
}



