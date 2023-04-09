#pragma once
#include "Entity.h"
#include "Map.h"



class Enemy :public Entity
{
private:

public:
	/*Enemy(sf::String File, float x, float y, float w, float h)*/
	Enemy(sf::Image* File, sf::String name, float x, float y, float w, float h);
	void ProcEvent(Entity* other, PostCode Code);
	void update(float time, std::list<Entity*>  *pEnemies = nullptr, Entity* pMyTank = nullptr);
	int getId();
};

