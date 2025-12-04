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
	bool m_isPlayerMissile = false;
	int m_lastAlienHitScore = 0;
public:
	using GameObject::GameObject;
	Missile() = default;
	Missile(Vector2 pos, char body, bool playersMissile);
	Missile(int xPos, int yPos, char body, bool playersMissile);
	virtual void update() override;
	void fireMissile(Vector2 pos);

	void setMissileDamage(int damage) { m_damage = damage; }
	int getMissileDamage() const { return m_damage; }
	int getAlienHitScore() const { return m_lastAlienHitScore; }
	bool isMissileActive() const { return m_isActive; }
	void setMissileActive(bool active) { m_isActive = active; }
	bool collisionDetection(std::vector<Alien>& aliens);
	bool collisionDetection(std::vector<Barrier>& barriers);
	bool collisionDetection(GameObject& player);
	//from https://www.w3schools.com/cpp/cpp_templates.asp
	
};

