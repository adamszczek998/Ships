#include "Simulation.h"
#include <conio.h>
#include <iostream>

using namespace std;;

void Simulation::Run()
{
	Init();
	projectiles.Commit();
	char choose;
	while (true)
	{
		cout << "---------------------------------Next frame---------------------------------\n";
		projectiles.DisplayAll();
		projectiles.FrameAll();
		
		Frame();
		projectiles.Commit();
		cout << "****************************************************************************\n";
		cout << "Press 'e' to exit simulation\n";
		choose = _getch(); //only windows
		if (choose == 'e')
			break;
	}
}
