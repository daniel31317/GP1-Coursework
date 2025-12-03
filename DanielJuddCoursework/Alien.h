#pragma once
#include "GameObject.h"
class Alien : public GameObject
{
	private:
		int m_health = 0;
		bool m_movingRight = true;
	public:
		using GameObject::GameObject;
		void setPlayerHealth(int health);
		int getPlayerHealth();
		bool moveAlien(Vector2 gameSize);
		void switchDirection();
};

