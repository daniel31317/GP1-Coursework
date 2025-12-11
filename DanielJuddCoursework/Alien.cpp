#include "Alien.h"
Alien::Alien(Vector2 pos, char body, WORD colour, int score) : GameObject(pos, body, colour), m_scoreForKill(score)
{

}

//move aliens
bool Alien::moveAlien(Vector2 gameSize)
{
	if (m_movingRight)
	{
		move(1, 0);
	}
	else
	{
		move(-1, 0);
	}

	if (m_position.x == 0 || m_position.x == gameSize.x - 2)
	{	
		if (m_movingRight)
		{
			move(-1, 0);
		}
		else
		{
			move(1, 0);
		}
		return true;
	}

	return false;
}

//change direction
void Alien::switchDirection()
{
	m_movingRight = !m_movingRight;
}


