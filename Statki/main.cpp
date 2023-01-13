#include <SFML/Graphics.hpp>
#include "Game.h"
#include <windows.h>

int main(){
	
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	//ShowWindow(hWnd, SW_SHOW);
	Game Gra;
	Gra.PlayGame();



	return 0;
}