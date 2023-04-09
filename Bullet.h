#pragma once
#include "Entity.h"
#include "Map.h"
#include <list>
#include "Game.h"

class Bullet :public Entity {//класс пули
private:
	bool AtMyTank; //Переменная указывающая урон по кому должен наносить снаряд - По моему танку AtMyTank == 1 или нет?;
	//
	Game* game;

public:
	void ProcEvent(Entity* other, PostCode Code);
	/*Bullet(float x, float y, int W, int H, int dir, bool AtMyTank, Game* game);*/
	Bullet(float x, float y, int W, int H, int dir, bool AtMyTank, Game* game, int TankID);
	//	   2
	//     ↑
	//     |
	//1 ←  0  -→ 0
	//     |
	//     ↓
	//	   3

	void update(float time, std::list<Entity*>  *pEnemies, Entity* pMyTank = nullptr);
	~Bullet();
};

