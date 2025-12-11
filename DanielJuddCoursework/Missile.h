#pragma once
#include "Barrier.h"
#include "GameObject.h"
#include "Alien.h"
#include <Windows.h>
#include <vector>


class Missile : public GameObject
{
private:
	//missile stats
	int m_damage = 0;
	bool m_isActive = false;
	bool m_isPlayerMissile = false;
	int m_lastAlienHitScore = 0;

	//move delay
	const float m_maxMissleDelay = 0.05f;
	float m_currentMissileDelta = 0.0f;	

public:
	//constructors
	using GameObject::GameObject;
	Missile() = default;
	Missile(Vector2 pos, char body, WORD colour, bool playersMissile);
	Missile(int xPos, int yPos, char body, WORD colour, bool playersMissile);

	//game loop
	virtual void update(float deltaTime) override;
	void fireMissile(Vector2 pos);

	//getters/setters
	void setMissileDamage(int damage) { m_damage = damage; }
	int getMissileDamage() const { return m_damage; }
	int getAlienHitScore() const { return m_lastAlienHitScore; }
	bool isMissileActive() const { return m_isActive; }
	void setMissileActive(bool active) { m_isActive = active; }

	//collision
	bool collisionDetection(std::vector<Alien>& aliens);
	bool collisionDetection(std::vector<Barrier>& barriers);
	bool collisionDetection(GameObject& gameObject);
	
};

