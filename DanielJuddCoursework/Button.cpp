#include "Button.h"

Button::Button()
{
	m_width = 0;
	m_height = 0;
	m_position = Vector2();
	m_drawPosition = Vector2();
	m_name = "";
}

Button::Button(int width, int height, Vector2 position, std::string name)
{
	m_width = width;
	m_height = height;
	m_position = position;
	m_drawPosition = Vector2(m_position.x - m_width / 2, m_position.y - m_height / 2);
	m_name = name;

	//prevent weird things from happening whilst initializing
	try
	{
		if (name.length() > m_width)
		{
			throw std::runtime_error("The button named - " + name + "'s length is greater than the width provided - " + std::to_string(m_width));
		}
		if (m_drawPosition.x < 0 || m_drawPosition.y < 0)
		{
			throw std::runtime_error("The button named - " + name + " will be drawn off screen");
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error - " << e.what();
		std::exit(EXIT_FAILURE);
	}

	m_buttonContent.resize(width);

	int nameIndex = 0;
	int nameStartPos = (width / 2) - (m_name.length() / 2);

	for (int i = 0; i < width; ++i) {
		m_buttonContent[i] = std::vector<char>(height);
		for (int j = 0; j < height; j++)
		{
			m_buttonContent[i][j] = getButtonDesignAtPosition(i, j, nameIndex, nameStartPos);
		}
	}
}



void Button::drawButton(GameWindow& window)
{
	Vector2 drawPos = m_drawPosition;

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			window.setCursorPosition(drawPos);
			std::cout << m_buttonContent[x][y];
			drawPos.y++;
		}
		drawPos.x++;
		drawPos.y = m_drawPosition.y;
	}
}

const char Button::getButtonDesignAtPosition(const int x, const int y, int& nameIndex, const int nameStartPos)
{
	const char corner = 'O';
	const char horizontalLine = '-';
	const char verticalLine = '|';
	const char space = ' ';

	if ((x == 0 || x == m_width - 1) && (y == 0 || y == m_height - 1))
	{
		return corner;
	}

	if (x == 0 || x == m_width - 1)
	{
		return verticalLine;
	}

	if (y == 0 || y == m_height - 1)
	{
		return horizontalLine;
	}

	if (x >= nameStartPos && y == m_height / 2)
	{
		if (nameIndex < m_name.length())
		{
			nameIndex++;
			return m_name[nameIndex - 1];
		}
	}

	return space;
}


bool Button::buttonInput(const int x, const int y) const
{
	if (x < m_drawPosition.x || x >= m_drawPosition.x + m_width || y < m_drawPosition.y || y >= m_drawPosition.y + m_height)
	{
		return false;
	}
	return true;
}