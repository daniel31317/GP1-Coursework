#pragma once
#include "GameObject.h"
class Alien : public GameObject
{
	protected:
		int m_scoreForKill = 0;
		bool m_movingRight = true;

	public:

		//constructors
		using GameObject::GameObject;
		Alien(Vector2 pos, char body, WORD colour, int score);

		//getter
		int getScoreForKill() { return m_scoreForKill; }

		bool moveAlien(Vector2 gameSize);
		void switchDirection();
};

