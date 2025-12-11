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


	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	m_width = size.x;
	m_height = size.y;

	SMALL_RECT windowSize = { 0, 0, (short)m_width + 20, (short)m_height + 20 };
	if (!SetConsoleWindowInfo(hStdOut, TRUE, &windowSize))
	{
		std::cout << "SetConsoleWindowIngo failed with error" << GetLastError() << std::endl;
	}
	if (!SetConsoleTitle(L"Daniel Judd Coursework"))
	{
		std::cout << "Set ConsoleTitle failed with error" << GetLastError() << std::endl;
	}

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hStdOut, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hStdOut, &cursorInfo);

	SetConsoleOutputCP(CP_UTF8);
}

void GameWindow::setCursorPosition(const int x, const int y)
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hStdOut, coord);
}

void GameWindow::setCursorPosition(const Vector2 pos)
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)pos.x, (SHORT)pos.y };
	SetConsoleCursorPosition(hStdOut, coord);
}

//https://stackoverflow.com/questions/9274745/using-writeconsoleoutputcharacter-and-setconsoletextattribute/9275247#9275247
void GameWindow::drawCharToScreen(const Vector2& pos, const BufferCell& cell) const
{
	COORD here{ static_cast<SHORT>(pos.x) , static_cast<SHORT>(pos.y) };
	WORD attribute = cell.colour;
	DWORD written;
	::WriteConsoleOutputAttribute(hStdOut, &attribute, 1, here, &written);
	::WriteConsoleOutputCharacterA(hStdOut, &cell.character, 1, here, &written);
}

void GameWindow::drawCharToScreen(const int x, const int y, const BufferCell& cell) const
{
	COORD here{ static_cast<SHORT>(x) , static_cast<SHORT>(y) };
	WORD attribute = cell.colour;
	DWORD written;
	::WriteConsoleOutputAttribute(hStdOut, &attribute, 1, here, &written);
	::WriteConsoleOutputCharacterA(hStdOut, &cell.character, 1, here, &written);
}

void GameWindow::drawWordToScreen(const Vector2& pos, const std::string& word, const WORD& color) const
{
	COORD here{ static_cast<SHORT>(pos.x) , static_cast<SHORT>(pos.y) };
	WORD attribute = color;
	DWORD written;

	for (int i = 0; i < word.length(); i++)
	{
		::WriteConsoleOutputAttribute(hStdOut, &attribute, 1, here, &written);
		::WriteConsoleOutputCharacterA(hStdOut, &word[i], 1, here, &written);
		here.X++;
	}

}