#pragma once
#include <memory>
#include <vector>
#include "Alien.h"
#include "ScreenBuffer.h"

class AlienManager
{
private:
	const Vector2 m_gameSize;

	std::vector<Alien> m_aliens;
	
	const int NUMBER_OF_ALIENS = 45;

	const float m_maxAlienMoveDelay = 1.5f;
	float m_currentAlienMoveDelay = m_maxAlienMoveDelay;
	float m_currentAlienMoveDelta = 0;

public:
	AlienManager();
	void initialiseAliens();
	void update(float deltaTime);
	void updateBuffer(ScreenBuffer& buffer);
	std::vector<Alien>* getAliens() { return &m_aliens; }
	void reduceDelay();
	const int getNumberOfAliens() { return m_aliens.size(); }
};

