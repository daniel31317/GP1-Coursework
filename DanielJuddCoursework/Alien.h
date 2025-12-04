#pragma once
#include "GameObject.h"
class Alien : public GameObject
{
	private:
		int m_scoreForKill = 0;
		bool m_movingRight = true;
	public:
		using GameObject::GameObject;
		Alien(Vector2 pos, char body, int score);
		int getScoreForKill() { return m_scoreForKill; }
		bool moveAlien(Vector2 gameSize);
		void switchDirection();
};

