#include <iostream>
#include <conio.h>
#include "BattlefieldSimulation.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char**argv)
{
	setlocale(LC_ALL, "Polish");
	srand(time(NULL));
	Simulation* sim = new BattlefieldSimulation;
	sim->Run();
	delete sim;
	return 0;
}