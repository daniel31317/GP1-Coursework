#pragma once
#include "GameObject.h"

class Player;

class Barrier : public GameObject
{
private :
	//space invader stuff
	char m_barrierStates[4] = { ' ', '-', '+', '#' };
	int m_barrierHealth = 3;

	//frogger stuff
	bool m_movingRight = true;
	bool m_isHarmful = true;
	float m_moveDelay = 0.0f;
	float m_moveDelta = 0.0f;
	Player* m_playerRef = nullptr;

public:
	//constructors
	using GameObject::GameObject;
	Barrier() = default;
	Barrier(int xPos, int yPos, char body, WORD colour, bool isMovingright, bool isHarmful, float maxMoveDelay);
	Barrier(Vector2 pos, char body, WORD colour, bool isMovingright, bool isHarmful, float maxMoveDelay);

	void damageBarrier();

	//getters
	int getBarrierHealth() const { return m_barrierHealth; }
	bool isActive() const { return m_barrierHealth == 0; }

	//game loop
	virtual void update(float deltaTime) override;
	void playerCollision(Player& player);
};

