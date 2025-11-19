#pragma once
#include "Barrier.h"
#include "GameObject.h"
#include "Alien.h"
#include <Windows.h>
#include <vector>

class Missile : public GameObject
{
private:
	int m_damage = 0;
	bool m_isActive = false;
public:
	using GameObject::GameObject;

	virtual void update() override;
	void fireMissile(Vector2 pos);
	void missileCollisionDetection(std::vector<Alien>& aliens, std::vector<Barrier>& barriers);

	void setMissileDamage(int damage) { m_damage = damage; }
	int getMissileDamage() const { return m_damage; }
	bool isMissileActive() const { return m_isActive; }
	void setMissileActive(bool active) { m_isActive = active; }

	
};

