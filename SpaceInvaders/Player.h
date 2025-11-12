#pragma once
#include "GameObject.h"
#include "Missile.h"
#include <Windows.h>
class Player : public GameObject
{
	private:
		int m_health = 0;
		Missile m_missile;
	public:
		using GameObject::GameObject;
		Player();
		Player(int xPos, int yPos, char body, int health);

		void processInput();
		void update() override;

		void setPlayerHealth(int health) { m_health = health; }
		int getPlayerHealth() const { return m_health; }
		Missile* getMissile() { return &m_missile; }
};

