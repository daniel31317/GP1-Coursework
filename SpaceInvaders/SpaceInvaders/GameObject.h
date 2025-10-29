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
		void move(int x, int y);
		void move(Vector2 move);
		void setPosition(int x, int y);
		void setPosition(Vector2 position);
		Vector2 getPosition();
		void setBody(char);
		char getbody();
		void draw();
};

