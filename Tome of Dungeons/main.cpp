#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "Engine.h"
#include <Windows.h>

using namespace std;

int main()
{
	//get a handle to the console window
	HWND console = GetConsoleWindow();
	RECT console_size;
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	//store the console window size in console_size
	GetWindowRect(console, &console_size);
	//reposition the console window so it is positioned and sized correctly
	//if we take the screen width or height and subrtact the game window width or height then divide by 2
	//it centers the screen
	MoveWindow(console, (screen_width - 800) / 2, (screen_height - 600) / 2, 800, 600, TRUE); // 800 width, 600 height
	Engine Engine("map_start_area.txt");

	// call the runGame function
	Engine.runGame();

	return 0;
}

