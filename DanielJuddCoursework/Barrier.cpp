#include "Barrier.h"
#include "Player.h"

Barrier::Barrier() : GameObject()
{
	
}
Barrier::Barrier(int xPos, int yPos, char body, WORD colour) : GameObject(xPos, yPos, body, colour)
{

}
Barrier::Barrier(int xPos, int yPos, char body, WORD colour, bool isMovingright, bool isHarmful, float maxDelay) : GameObject(xPos, yPos, body, colour)
, m_movingRight(isMovingright), m_isHarmful(isHarmful), m_moveDelay(maxDelay)
{
	
}

Barrier::Barrier(Vector2 pos, char body, WORD colour, bool isMovingright, bool isHarmful, float maxDelay) : GameObject(pos, body, colour)
, m_movingRight(isMovingright), m_isHarmful(isHarmful), m_moveDelay(maxDelay)
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

void Barrier::update(float deltaTime)
{
	m_moveDelta += deltaTime;

	if (m_moveDelta < m_moveDelay)
	{
		return;
	}

	m_moveDelta = 0.0f;

	if (m_movingRight)
	{
		if (m_position.x < 78)
		{
			move(1, 0);
			if(m_playerRef != nullptr)
			{
				m_playerRef->move(1, 0);
			}
		}
		else
		{
			m_position.x = 1;
			if (m_playerRef != nullptr)
			{
				m_playerRef->loseLife();
			}
		}
	}
	else
	{
		if (m_position.x > 0)
		{
			move(-1, 0);
			if (m_playerRef != nullptr)
			{
				m_playerRef->move(-1, 0);
			}
		}
		else
		{
			m_position.x = 78;
			if (m_playerRef != nullptr)
			{
				m_playerRef->loseLife();
			}
		}
	}
}

void Barrier::playerCollision(Player& player)
{
	if (isColliding(player))
	{
		if(m_isHarmful)
		{
			player.loseLife();
			return;
		}
		else
		{
			m_playerRef = &player;
			return;
		}
	}
	m_playerRef = nullptr;
}


