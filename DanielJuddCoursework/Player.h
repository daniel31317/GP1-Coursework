#pragma once
#include "GameObject.h"
#include "Missile.h"
#include <Windows.h>
class Player : public GameObject
{
	private:
		//both
		int m_lives = 4;
		bool m_isSpaceInvaders = true;
		const float m_moveDelay = 0.1f;
		float m_moveDelta = 0.0f;

		//space invaders
		Missile m_missile;
		
		//frogger
		int highestYPosition = 0;
		
	public:
		using GameObject::GameObject;

		//constructors
		Player();
		Player(int xPos, int yPos, char body, WORD colour, bool isGameSpaceInvaders);

		//game loop
		void processInput(float deltaTime);
		virtual void update(float deltaTime) override;

		//logic
		void loseLife() { m_lives--; }
		int getPlayerLives() const { return m_lives; }
		void setPlayerLives(int health) { m_lives = health; }
		int getHighestYPosition() const { return highestYPosition; }
		void setHighestYPosition(int yPos) { highestYPosition = yPos; }
		Missile* getMissile() { return &m_missile; }
};

