#pragma once
#include <Windows.h>

// Enum must align exactly with the indices used in ColourCodes array.
enum Colour
{
	Black = 0,
	White = 1,
	DarkBlue = 2,
	DarkGreen = 3,
	DarkCyan = 4,
	DarkRed = 5,
	DarkPink= 6,
	DarkYellow = 7,
	LightGray = 8,
	Gray = 9,           
	Blue = 10,
	Green = 11,
	Cyan = 12,
	Red = 13,
	Pink = 14,
	Yellow = 15,
	
};


static const WORD ColourCodes[] =
{
	0,     
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	FOREGROUND_BLUE,                           
	FOREGROUND_GREEN,                        
	FOREGROUND_GREEN | FOREGROUND_BLUE,         
	FOREGROUND_RED,                           
	FOREGROUND_RED | FOREGROUND_BLUE,        
	FOREGROUND_RED | FOREGROUND_GREEN,         
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 
	FOREGROUND_INTENSITY,                   
	FOREGROUND_BLUE | FOREGROUND_INTENSITY,    
	FOREGROUND_GREEN | FOREGROUND_INTENSITY,   
	FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, 
	FOREGROUND_RED | FOREGROUND_INTENSITY,    
	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,  
	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};