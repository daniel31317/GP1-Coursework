#pragma once
#include "Vector2.h"
#include "GameWindow.h"
#include <string>

class Button
{
private:
	int m_width, m_height;
	Vector2 m_position;
	Vector2 m_drawPosition;
	std::string m_name;
	char** m_buttonContent;

	const char getButtonDesignAtPosition(const int x, const int y, int& nameIndex, const int nameStartPos);
	
public:
	Button();
	~Button();
	Button(int width, int height, Vector2 position, std::string name);
	void drawButton(GameWindow& window);
	bool buttonInput(const int x, const int y);

	
};

