#pragma once
#include "GameObject.h"
class Alien : public GameObject
{
	private:
		int m_health;
	public:
		using GameObject::GameObject;
		void setPlayerHealth(int health);
		int getPlayerHealth();
};

