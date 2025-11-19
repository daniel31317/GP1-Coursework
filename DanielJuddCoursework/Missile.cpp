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

	m_position = pos;
	m_position.y--;
	m_isActive = true;
}

void Missile::missileCollisionDetection(std::vector<Alien>& aliens, std::vector<GameObject>& barriers)
{
	if (m_position.y < 0)
	{
		m_isActive = false;
		return;
	}

	for (int i = 0; i < aliens.size(); i++)
	{
		if (aliens[i].getPosition() == m_position)
		{
			//swap that element to with the back then pop it 
			//this is better because we aren't shifting the rest of the vector after the index we want to remove
			std::swap(aliens[i], aliens.back());
			aliens.pop_back();
			m_isActive = false;
			return;
		}
	}

	for (int i = 0; i < barriers.size(); i++)
	{
		if (barriers[i].getPosition() == m_position)
		{
			std::swap(barriers[i], barriers.back());
			barriers.pop_back();
			m_isActive = false;
			return;
		}
	}
}
