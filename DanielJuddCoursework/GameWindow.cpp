#include "GameWindow.h"

void GameWindow::setWindow(int width, int height)
{
	m_width = width;
	m_height = height;

	SMALL_RECT windowSize = { 10, 10, (short)width + 20, (short)height + 20 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
	{
		std::cout << "SetConsoleWindowIngo failed with error" << GetLastError() << std::endl;
	}
	if (!SetConsoleTitle(L"Daniel Judd Coursework"))
	{
		std::cout << "Set ConsoleTitle failed with error" << GetLastError() << std::endl;
	}

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // this code hides the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);

	SetConsoleOutputCP(CP_UTF8);
}

void GameWindow::setCursorPosition(const int x, const int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void GameWindow::setCursorPosition(const Vector2 pos)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)pos.x, (SHORT)pos.y };
	SetConsoleCursorPosition(hOut, coord);
}