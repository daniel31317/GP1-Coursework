#pragma once
#include <iostream>
#include <Windows.h>
#include "Vector2.h"
#include "ScreenBuffer.h"
class GameWindow
{
private:
	//initial values
	int m_width = 0;
	int m_height = 0;
	HANDLE hStdOut;
public:
	void setWindow(Vector2 size);
	void setCursorPosition(const int x, const int y);
	void setCursorPosition(const Vector2 position);
	void drawCharToScreen(const Vector2& pos, const BufferCell& cell) const;
	void drawWordToScreen(const Vector2& pos, const std::string& word, const WORD& color) const;
};

