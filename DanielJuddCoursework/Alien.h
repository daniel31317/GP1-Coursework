#pragma once
#include "GameObject.h"
class Alien : public GameObject
{
	private:
		int m_health = 0;
		int m_scoreForKill = 0;
		bool m_movingRight = true;
	public:
		using GameObject::GameObject;
		Alien(Vector2 pos, char body, int score);
		void setPlayerHealth(int health) { m_health = health; }
		int getPlayerHealth() { return m_health; }
		int getScoreForKill() { return m_scoreForKill; }
		bool moveAlien(Vector2 gameSize);
		void switchDirection();
};

