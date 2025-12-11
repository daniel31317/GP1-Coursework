#pragma once
#include "Vector2.h"
#include "GameWindow.h"
#include <string>
#include <vector>

class Button
{
private:
	//store constant design chars
	const char corner = 'O';
	const char horizontalLine = '-';
	const char verticalLine = '|';
	const char space = ' ';

	int m_width, m_height;

	Vector2 m_position;
	Vector2 m_drawPosition;

	std::string m_name;

	WORD m_borderColour;
	WORD m_nameColour;

	//stores all the chars and colours (buffer cell) for the button
	std::vector<std::vector<BufferCell>> m_buttonContent;

	BufferCell getButtonDesignAtPosition(const int x, const int y, int& nameIndex, const int nameStartPos);
	
public:
	//constructors
	Button();
	Button(int width, int height, Vector2 position, std::string name, WORD borderColour, WORD nameColour);

	//drawing
	void drawButton(GameWindow& window);

	bool buttonInput(const int x, const int y) const;

	void setPosition(const int x, const int y) { m_position = Vector2(x, y); m_drawPosition = Vector2(x - m_width / 2, y - m_height / 2);}

	
};

