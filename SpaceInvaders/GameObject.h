#pragma once
#include <iostream>
#include "Vector2.h"


class GameObject
{
	protected:
		Vector2 position;
		char body;

	public:
		GameObject();
		GameObject(int xPos, int yPos, char body);
		GameObject(Vector2 position, char body);

		void draw();
		virtual void update();
		void move(int x, int y);
		void move(Vector2 move);

		void setPosition(int x, int y) { position.x = x; position.y = y; }
		void setPosition(Vector2 position) { this->position = position; }
		Vector2 getPosition() const { return position; };

		void setBody(char body) { this->body = body; }
		char getBody() const { return body; }
		
};

