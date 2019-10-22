#ifndef _BATTLEFIELDSIMULATION_H
#define _BATTLEFIELDSIMULATION_H
#include "Simulation.h"

class BattlefieldSimulation : public Simulation
{
protected:
	void Frame() override {};
	void Init() override {
		//Projectile* nowyPocisk = new Projectile;
		//this->projectiles.Add(nowyPocisk);
	}

};

#endif