#pragma once
#include "GameObject.h"
#include <Windows.h>
class Player : public GameObject
{
	private:
		int m_health;
	public:
		using GameObject::GameObject;
		void processInput();
		void setPlayerHealth(int health);
		int getPlayerHealth();
};

