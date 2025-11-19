#pragma once
#include <iostream>
#include "Vector2.h"
#include <Windows.h>

class GameObject
{
	protected:
		Vector2 m_position;
		char m_body;

	public:
		GameObject();
		GameObject(int xPos, int yPos, char body);
		GameObject(Vector2 position, char body);

		void draw() const;
		virtual void update();
		void move(int x, int y);
		void move(Vector2 move);

		void setPosition(int x, int y) { m_position.x = x; m_position.y = y; }
		void setPosition(Vector2 position) { this->m_position = position; }
		Vector2 getPosition() const { return m_position; };

		void setBody(char body) { this->m_body = body; }
		char getBody() const { return m_body; }
		
};

