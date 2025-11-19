#pragma once
#include "GameObject.h"
#include "Missile.h"
#include <Windows.h>
class Player : public GameObject
{
	private:
		int m_lives = 0;
		Missile m_missile;
		bool m_isSpaceInvaders = true;
	public:
		using GameObject::GameObject;
		Player();
		Player(int xPos, int yPos, char body, int lives, bool isGameSpaceInvaders);

		void processInput();
		virtual void update() override;

		void setPlayerHealth(int health) { m_lives = health; }
		int getPlayerHealth() const { return m_lives; }
		Missile* getMissile() { return &m_missile; }
};

