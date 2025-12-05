#include "AlienManager.h"

AlienManager::AlienManager()
{
	m_aliens.reserve(NUMBER_OF_ALIENS);
	m_missiles.reserve(NUMBER_OF_MISSILES);
	srand(unsigned int(time(0)));

	m_currentAlienShootDelay = (m_maxAlienShootDelay - m_minAlienShootDelay) * ((float)rand() / RAND_MAX) + m_minAlienShootDelay;
}

void AlienManager::initialiseAliens()
{
	m_aliens.clear();
	m_missiles.clear();

	Vector2 pos = Vector2(20, 5);
	int scoreForAlien = 50;

	for (int i = 0; i < NUMBER_OF_ALIENS; i++)
	{
		if (i % 9 == 0 && i != 0)
		{
			pos.x = 20;
			pos.y += 2;
			scoreForAlien -= 10;
		}
		m_aliens.emplace_back(pos, 'A', ColourCodes[Green], scoreForAlien);
		pos.x += 5;
	}

	for (int i = 0; i < NUMBER_OF_MISSILES; i++)
	{
		m_missiles.emplace_back(0, 0, '!', ColourCodes[Red], false);
	}

	m_specialAlien = SpecialAlien(Vector2(0, 0), 'A', ColourCodes[Blue], 100);
}


void AlienManager::update(float deltaTime, Player& player, std::vector<Barrier>& barriers)
{
	m_currentAlienMoveDelta += deltaTime;
	m_currentAlienShootDelta += deltaTime;

	if(!m_specialAlien.isActive())
	{
		if (rand() % 1000 < 5)
		{
			m_specialAlien.spawn(Vector2(0, 0));
		}
	}

	if (m_currentAlienMoveDelta >= m_currentAlienMoveDelay)
	{
		for (int i = 0; i < m_aliens.size(); i++)
		{
			if (m_aliens[i].moveAlien(m_gameSize))
			{
				for (int j = 0; j < m_aliens.size(); j++)
				{
					m_aliens[j].switchDirection();
					m_aliens[j].move(0, 1);
				}

				for (int j = 0; j < i; j++)
				{
					m_aliens[j].moveAlien(m_gameSize);
				}

				break;
			}
		}
		m_currentAlienMoveDelta = 0;
	}

	for (int i = 0; i < m_missiles.size(); i++)
	{
		m_missiles[i].update(deltaTime);

		if (m_currentAlienShootDelta >= m_currentAlienShootDelay)
		{
			if (!m_missiles[i].isMissileActive())
			{
				m_missiles[i].fireMissile(m_aliens[rand() % m_aliens.size()].getPosition());
				m_currentAlienShootDelta = 0;
				m_currentAlienShootDelay = (m_maxAlienShootDelay - m_minAlienShootDelay) * ((float)rand() / RAND_MAX) + m_minAlienShootDelay;
			}
		}

		if(m_missiles[i].collisionDetection(player))
		{
			player.loseLife();
		}

		//do an additional check for the y co-ordinate just so we dont have to loop through every barrier for every missile
		if (barriers.size() > 0 && barriers[0].getPosition().y == m_missiles[i].getPosition().y)
		{
			m_missiles[i].collisionDetection(barriers);
		}
	}


	if (m_specialAlien.isActive())
	{
		m_specialAlien.update(deltaTime);
	}

}

void AlienManager::updateBuffer(ScreenBuffer& buffer)
{
	for (int i = 0; i < m_aliens.size(); i++)
	{
		buffer.setGameObjectAtPos(m_aliens[i]);
	}

	for (int i = 0; i < m_missiles.size(); i++)
	{
		if (m_missiles[i].isMissileActive())
		{
			buffer.setGameObjectAtPos(m_missiles[i]);
		}
	}

	if (m_specialAlien.isActive())
	{
		buffer.setGameObjectAtPos(m_specialAlien);
	}
	
}

void AlienManager::reduceDelay()
{
	m_currentAlienMoveDelay -= 0.02f;
}

int AlienManager::getLowestAlienY()
{
	int lowestY = 0;
	for(int i = 0; i < m_aliens.size(); i++)
	{
		if (m_aliens[i].getPosition().y > lowestY)
		{
			lowestY = m_aliens[i].getPosition().y;
		}
	}

	return lowestY;
}
