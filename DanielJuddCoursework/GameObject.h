#pragma once
#include <iostream>
#include "Vector2.h"
#include "Colour.h"
#include <Windows.h>

class GameObject
{
	protected:
		Vector2 m_position;
		char m_body;
		WORD m_colour = ColourCodes[White];

	public:
		//constructors
		GameObject();
		GameObject(int xPos, int yPos, char body, WORD colour);
		GameObject(Vector2 position, char body, WORD colour);

		//game loop
		void draw() const;
		virtual void update(float deltaTime);

		//movement
		void move(int x, int y);
		void move(Vector2 move);

		//getters/setters
		void setPosition(int x, int y) { m_position.x = x; m_position.y = y; }
		void setPosition(Vector2 position) { this->m_position = position; }
		Vector2 getPosition() const { return m_position; };

		void setColour(WORD colour) { m_colour = colour; }
		WORD getColour() const { return m_colour; };

		void setBody(char body) { this->m_body = body; }
		char getBody() const { return m_body; }

		bool isColliding(const GameObject& other) const { return m_position == other.m_position; }
		
};

