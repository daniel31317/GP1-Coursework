#include "AlienManager.h"

AlienManager::AlienManager()
{
	
}

void AlienManager::initialiseAliens()
{
	m_aliens.clear();

	m_aliens.reserve(NUMBER_OF_ALIENS);

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
		m_aliens.emplace_back(Alien(pos, 'A', scoreForAlien));
		pos.x += 5;
	}
}

void AlienManager::update(float deltaTime)
{
	m_currentAlienMoveDelta += deltaTime;

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
}

void AlienManager::updateBuffer(ScreenBuffer& buffer)
{
	for (int i = 0; i < m_aliens.size(); i++)
	{
		buffer.setGameObjectAtPos(m_aliens[i]);
	}
}

void AlienManager::reduceDelay()
{
	m_currentAlienMoveDelay -= 0.02f;
}
