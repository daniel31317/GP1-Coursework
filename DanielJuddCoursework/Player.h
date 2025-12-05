#pragma once
#include "GameObject.h"
#include "Missile.h"
#include <Windows.h>
class Player : public GameObject
{
	private:
		int m_lives = 4;
		Missile m_missile;
		bool m_isSpaceInvaders = true;

		const float m_moveDelay = 0.05f;
		float m_moveDelta = 0.0f;
	public:
		using GameObject::GameObject;
		Player();
		Player(int xPos, int yPos, char body, WORD colour, bool isGameSpaceInvaders);

		void processInput(float deltaTime);
		virtual void update(float deltaTime) override;

		void loseLife() { m_lives--; }
		int getPlayerLives() const { return m_lives; }
		void setPlayerLives(int health) { m_lives = health; }
		Missile* getMissile() { return &m_missile; }
};

