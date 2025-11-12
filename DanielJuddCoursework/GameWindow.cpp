#include "GameWindow.h"

void GameWindow::setWindow(Vector2 size)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	m_width = size.x;
	m_height = size.y;


	SMALL_RECT windowSize = { 0, 0, (short)m_width + 20, (short)m_height + 20 };
	if (!SetConsoleWindowInfo(hOut, TRUE, &windowSize))
	{
		std::cout << "SetConsoleWindowIngo failed with error" << GetLastError() << std::endl;
	}
	if (!SetConsoleTitle(L"Daniel Judd Coursework"))
	{
		std::cout << "Set ConsoleTitle failed with error" << GetLastError() << std::endl;
	}

	

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hOut, &cursorInfo);

	SetConsoleOutputCP(CP_UTF8);
}

void GameWindow::setCursorPosition(const int x, const int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void GameWindow::setCursorPosition(const Vector2 pos)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)pos.x, (SHORT)pos.y };
	SetConsoleCursorPosition(hOut, coord);
}