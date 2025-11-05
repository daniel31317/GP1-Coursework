#pragma once
#include "GameObject.h"
#include "Alien.h"
#include <Windows.h>

class Missile : public GameObject
{
private:
	int m_damage = 0;
	bool m_isActive = false;
public:
	using GameObject::GameObject;

	void update() override;
	void fireMissile(Vector2 pos);
	void missileCollisionDetection(const Alien* aliens, const int NUMBER_OF_ALIENS, const GameObject* barriers, const int NUMBER_OF_BARRIERS);

	void setMissileDamage(int damage) { m_damage = damage; }
	int getMissileDamage() { return m_damage; }
	bool isMissileActive() { return m_isActive; }
	void setMissileActive(bool active) { m_isActive = active; }

	
};

