#pragma once
#include <iostream>
#include <Windows.h>
#include "Vector2.h"
class GameWindow
{
private:
	//initial values
	int m_width = 0;
	int m_height = 0;
public:
	void setWindow(Vector2 size);
	void setCursorPosition(const int x, const int y);
	void setCursorPosition(const Vector2 position);
};

