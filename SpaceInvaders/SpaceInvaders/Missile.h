#pragma once
#include "GameObject.h"
class Missile : public GameObject
{
private:
	int m_damage;
public:
	using GameObject::GameObject;
	void setMissileDamage(int damage);
	int getMissileDamage();
};

