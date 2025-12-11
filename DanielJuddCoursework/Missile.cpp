#include "Missile.h"

//constructors
Missile::Missile(Vector2 pos, char body, WORD colour, bool playersMissile) : GameObject(pos, body, colour), m_isPlayerMissile(playersMissile)
{

}

Missile::Missile(int xPos, int yPos, char body, WORD colour, bool playersMissile) : GameObject(xPos, yPos, body, colour), m_isPlayerMissile(playersMissile)
{

}



void Missile::update(float deltaTime)
{
	if (!m_isActive)
	{
		return;
	}

	m_currentMissileDelta += deltaTime;

	if(m_currentMissileDelta < m_maxMissleDelay)
	{
		return;
	}

	//move missile up on screen (down in y direction) if its players
	m_currentMissileDelta = 0.0f;
	if (m_isPlayerMissile)
	{			
		move(0, -1);
		if (m_position.y < 0)
		{
			m_isActive = false;
		}
	}
	//smae thing but opposite as it is aliens	
	else
	{
		move(0, 1);
		if (m_position.y > 80)
		{
			m_isActive = false;
		}
		
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
	m_isActive = true;

	if (m_isPlayerMissile)
	{
		m_position.y--;
	}
	else
	{
		m_position.y++;
	}
}

bool Missile::collisionDetection(std::vector<Alien>& aliens)
{
	if (!m_isActive)
	{
		return false;
	}

	//loop thoroufh aliens and check if colliding
	for (int i = 0; i < aliens.size(); i++)
	{
		if (isColliding(aliens[i]))
		{
			m_lastAlienHitScore = aliens[i].getScoreForKill();
			//swap that element to with the back then pop it 
			//this is better because we aren't shifting the rest of the vector after the index we want to remove
			std::swap(aliens[i], aliens.back());
			aliens.pop_back();
			m_isActive = false;
			return true;
		}
	}

	return false;
}


//same as allien function but with barriers
bool Missile::collisionDetection(std::vector<Barrier>& barriers)
{
	if (!m_isActive)
	{
		return false;
	}

	for (int i = 0; i < barriers.size(); i++)
	{
		if (isColliding(barriers[i]))
		{
			barriers[i].damageBarrier();
			if (barriers[i].getBarrierHealth() == 0)
			{
				//swap that element to with the back then pop it 
				//this is better because we aren't shifting the rest of the vector after the index we want to remove
				std::swap(barriers[i], barriers.back());
				barriers.pop_back();
			}	
			m_isActive = false;
			return true;
		}
	}

	return false;
}

//same but only for player
bool Missile::collisionDetection(GameObject& gameObject)
{
	if (!m_isActive)
	{
		return false;
	}

	if (isColliding(gameObject))
	{
		m_isActive = false;
		return true;
	}

	return false;
}


