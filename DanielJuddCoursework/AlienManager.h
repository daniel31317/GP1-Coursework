#pragma once
#include <memory>
#include <vector>
#include "Alien.h"
#include "ScreenBuffer.h"
#include "Missile.h"
#include "Player.h"
#include "SpecialAlien.h"


class AlienManager
{
private:

	//makes the game source file more readable if aliens are handled in here

	Vector2 m_gameSize;

	std::vector<Alien> m_aliens;
	std::vector<Missile> m_missiles;

	SpecialAlien m_specialAlien;	
	
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
	//constructor
	AlienManager();
	void initialiseAliens();

	//game loop
	void update(float deltaTime, Player& player, std::vector<Barrier>& barriers);
	void updateBuffer(ScreenBuffer& buffer);

	//getters/setters
	void setGameSize(const Vector2 gameSize) { m_gameSize = gameSize; }
	std::vector<Alien>* getAliens() { return &m_aliens; }
	SpecialAlien* getSpecialAlien() { return &m_specialAlien; }
	void reduceDelay();
	int getNumberOfAliens() { return (int)m_aliens.size(); }
	int getLowestAlienY();
};

