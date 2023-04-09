#pragma once
#include "Entity.h"
#include "Map.h"
#include "View.h"
#include "Game.h"

class MyTank :public Entity
{
private:
	int score;
	int RKits;
	int time;
	void interactionWithMap(Tab* pScore, Game* game);
public:
	MyTank(sf::String File, float x, float y, float w, float h);
	void ProcEvent(Entity* other, PostCode Code);
	float getDx();
	float getDy();
	sf::FloatRect getRectDir();
	void update(float time, Tab* pScore, Game* game);
	int getPlayerRKit();
	int getPlayerHP();
	
	
};

