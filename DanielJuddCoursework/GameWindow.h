#pragma once
#include <iostream>
#include <Windows.h>
#include "Vector2.h"
class GameWindow
{
private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//initial values
	int m_width = 0;
	int m_height = 0;
public:
	void setWindow(int width, int height);
	void setCursorPosition(const int x, const int y);
	void setCursorPosition(const Vector2 position);
};

