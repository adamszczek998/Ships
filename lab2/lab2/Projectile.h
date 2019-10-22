#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#include "ProjectileCollection.h"
#include <iostream>
class ProjectileCollection;
class Projectile
{
public:
	void Display()
	{
		std::cout << "metoda print klasy Projectile\n";
	}
	void Frame(ProjectileCollection& projectiles)
	{
		std::cout << "metoda action klasy Projectile\n";
	}

};
#endif