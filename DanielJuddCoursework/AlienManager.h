#pragma once
#include <memory>
#include <vector>
#include "Alien.h"
#include "ScreenBuffer.h"
#include "Missile.h"
#include "Player.h"

class AlienManager
{
private:
	Vector2 m_gameSize;

	std::vector<Alien> m_aliens;
	std::vector<Missile> m_missiles;
	
	const int NUMBER_OF_ALIENS = 45;
	const int NUMBER_OF_MISSILES = 5;

	const float m_maxAlienMoveDelay = 1.5f;
	float m_currentAlienMoveDelay = m_maxAlienMoveDelay;
	float m_currentAlienMoveDelta = 0;

	const float m_maxAlienShootDelay = 2.0f;
	const float m_minAlienShootDelay = 0.1f;
	float m_currentAlienShootDelay = 0;
	float m_currentAlienShootDelta = 0;



public:
	AlienManager();
	void setGameSize(const Vector2 gameSize) { m_gameSize = gameSize; }
	void initialiseAliens();
	void update(float deltaTime, Player& player, std::vector<Barrier>& barriers);
	void updateBuffer(ScreenBuffer& buffer);
	std::vector<Alien>* getAliens() { return &m_aliens; }
	void reduceDelay();
	int getNumberOfAliens() const { return m_aliens.size(); }
};

