#include "GameWindow.h"

void GameWindow::setWindow(Vector2 size)
{
	//from https://stackoverflow.com/questions/79152088/how-to-change-console-size-on-windows-11
	HWND hwnd = GetConsoleWindow();
	Sleep(10);//If you execute these code immediately after the program starts, you must wait here for a short period of time, otherwise GetWindow will fail. I speculate that it may be because the console has not been fully initialized.
	HWND owner = GetWindow(hwnd, GW_OWNER);
	if (owner == NULL) {
		// Windows 10
		SetWindowPos(hwnd, nullptr, 0, 0, 815, 730, SWP_NOZORDER | SWP_NOMOVE);
	}
	else {
		// Windows 11
		SetWindowPos(owner, nullptr, 0, 0, 815, 730, SWP_NOZORDER | SWP_NOMOVE);
	}


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

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

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