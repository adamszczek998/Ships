#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#include "ProjectileCollection.h"
#include <iostream>
#include "Vector2D.h"
class ProjectileCollection;
class Projectile
{
protected:
	Vector2D pozycjaPocisku;
	Vector2D kierunekPocisku;
	float predkoscPocisku;
	std::string nazwaPocisku;
public:
	Projectile(const Vector2D& pozycjaPocisku, const Vector2D& kierunekPocisku, const float& predkoscPocisku, const std::string& nazwaPocisku) : pozycjaPocisku(pozycjaPocisku), kierunekPocisku(kierunekPocisku), predkoscPocisku(predkoscPocisku), nazwaPocisku(nazwaPocisku) { this->kierunekPocisku.normalise(); }

	virtual void Display()
	{
		std::cout << "Pozycja: ";
		pozycjaPocisku.Show();
		std::cout << "\nKierunek: ";
		kierunekPocisku.Show();
		std::cout << "\nPredkosc: " << predkoscPocisku << std::endl;
	}
	virtual void Frame(ProjectileCollection& projectiles) = 0;
	/*
	void Frame()
	{
		std::cout << "metoda action klasy Projectile\n";
	}
	*/
	void Shift() {
		pozycjaPocisku += kierunekPocisku * predkoscPocisku;
	}

};

class ClusterBomb {
	ClusterBomb(const Vector2D& pozycjaPocisku, const Vector2D& kierunekPocisku) : pozycjaPocisku(pozycjaPocisku), kierunekPocisku(kierunekPocisku) {}
};
class ShotgunShell {
	ShotgunShell(const Vector2D& pozycjaPocisku, const Vector2D& kierunekPocisku) : pozycjaPocisku(pozycjaPocisku), kierunekPocisku(kierunekPocisku) {}
};
class Cluster {
	Cluster(const Vector2D& pozycjaPocisku, const Vector2D& kierunekPocisku) : pozycjaPocisku(pozycjaPocisku), kierunekPocisku(kierunekPocisku) {}
};
#endif