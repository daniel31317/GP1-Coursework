#include "Button.h"

Button::Button()
{
	m_width = 0;
	m_height = 0;
	m_position = Vector2();
	m_drawPosition = Vector2();
	m_name = "";
	m_borderColour = ColourCodes[White];
	m_nameColour = ColourCodes[White];;
}

Button::Button(int width, int height, Vector2 position, std::string name, WORD borderColour, WORD nameColour) : m_width(width), m_height(height), m_position(position),
m_drawPosition(Vector2(m_position.x - m_width / 2, m_position.y - m_height / 2)), m_name(name), m_borderColour(borderColour), m_nameColour(nameColour)
{
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

	//reserve vector memory
	m_buttonContent.reserve(width);

	//get name start pos
	int nameIndex = 0;
	int nameStartPos = static_cast<int>((width / 2) - (m_name.length() / 2));

	for (int i = 0; i < width; ++i) {
		m_buttonContent.emplace_back(std::vector<BufferCell>(height));
		for (int j = 0; j < height; j++)
		{
			//fill in button content
			m_buttonContent[i][j] = getButtonDesignAtPosition(i, j, nameIndex, nameStartPos);
		}
	}
}


//draws the button to the screen
void Button::drawButton(GameWindow& window)
{
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			window.drawCharToScreen(x + m_drawPosition.x, y + m_drawPosition.y, m_buttonContent[x][y]);
		}
	}
}


//returns the correct buffer cell data for the point needed
BufferCell Button::getButtonDesignAtPosition(const int x, const int y, int& nameIndex, const int nameStartPos)
{
	if ((x == 0 || x == m_width - 1) && (y == 0 || y == m_height - 1))
	{
		return BufferCell(corner, m_borderColour);
	}

	if (x == 0 || x == m_width - 1)
	{
		return BufferCell(verticalLine, m_borderColour);
	}

	if (y == 0 || y == m_height - 1)
	{
		return BufferCell(horizontalLine, m_borderColour);
	}

	if (x >= nameStartPos && y == m_height / 2)
	{
		if (nameIndex < m_name.length())
		{		
			nameIndex++;
			return BufferCell(m_name[nameIndex - 1], m_nameColour);
		}
	}

	return BufferCell(space, m_borderColour);
}


//if the mouse is within these co-ordiantes then the button is clicked
bool Button::buttonInput(const int x, const int y) const
{
	if (x < m_drawPosition.x || x >= m_drawPosition.x + m_width || y < m_drawPosition.y || y >= m_drawPosition.y + m_height)
	{
		return false;
	}
	return true;
}