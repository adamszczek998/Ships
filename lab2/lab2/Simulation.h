#ifndef _SIMULATION_H
#define _SIMULATION_H
#include "ProjectileCollection.h"
class Simulation
{
protected:
	//wywolywane w kazdej klatce symulacji
	virtual void Frame() = 0;

	//Inicjalizacja gry - tutaj umieszczenie pociskow w symulacji
	virtual void Init() = 0;

	//Kolekcja wszystkich pocisków w symulacji
	ProjectileCollection projectiles;
public:

	//Start simulation
	void Run();
};


#endif