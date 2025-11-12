#include "Missile.h"

void Missile::update()
{
	if (m_isActive)
	{
		move(0, -1);
	}
}
void Missile::fireMissile(Vector2 pos)
{
	//if missile is already active return if not set position and make it active
	if (m_isActive)
	{
		return;
	}

	position = pos;
	position.y--;
	m_isActive = true;
}

void Missile::missileCollisionDetection(const Alien* aliens, const int NUMBER_OF_ALIENS, const GameObject* barriers, const int NUMBER_OF_BARRIERS)
{
	if (position.y < 0)
	{
		m_isActive = false;
		return;
	}

	for (int i = 0; i < NUMBER_OF_ALIENS; i++)
	{
		if (aliens[i].getPosition() == position)
		{
			m_isActive = false;
			return;
		}
	}

	for (int i = 0; i < NUMBER_OF_BARRIERS; i++)
	{
		if (barriers[i].getPosition() == position)
		{
			m_isActive = false;
			return;
		}
	}
}
