#include "ProjectileCollection.h"
using namespace std;
//#define VS_2010
void ProjectileCollection::Add(Projectile* projectile)
{
	to_add.insert(projectile);
}

void ProjectileCollection::Remove(Projectile* projectile)
{
	to_remove.insert(projectile);
}

void ProjectileCollection::FrameAll()
{
#ifndef VS_2010
	for (Projectile* projectile : projectiles)
		projectile->Frame(*this);
#else
	for (set<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it)
		(*it)->Frame(*this);
#endif
}

void ProjectileCollection::DisplayAll()
{
#ifndef VS_2010
	for (Projectile* projectile : projectiles)
		projectile->Display();
#else
	for (set<Projectile*>::iterator it = projectiles.begin(); it != projectiles.end(); ++it)
		(*it)->Display();
#endif
}


void ProjectileCollection::free_set_mem(set<Projectile*>& _data)
{
#ifndef VS_2010
	for (auto projectile : _data)
		delete projectile;
#else
	for (set<Projectile*>::iterator it = _data.begin(); it != _data.end(); ++it)
		delete *it;
#endif
}

ProjectileCollection::~ProjectileCollection()
{
	free_set_mem(projectiles);
	free_set_mem(to_add);
	free_set_mem(to_remove);
}

void ProjectileCollection::Commit()
{
#ifndef VS_2010
	for (auto projectile : to_remove)
	{
		auto it = projectiles.find(projectile);
		delete *it;
		projectiles.erase(it);
	}
#else
	for (set<Projectile*>::iterator it = to_remove.begin(); it != to_remove.end(); ++it)
	{
		set<Projectile*>::iterator found_it = projectiles.find(*it);
		delete *found_it;
		projectiles.erase(found_it);
	}
#endif
	to_remove.clear();
	projectiles.insert(to_add.begin(), to_add.end());
	to_add.clear();
}


