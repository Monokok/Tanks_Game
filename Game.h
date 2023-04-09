#pragma once
#include "Map.h"
#include "Enemy.h"

class Game
{
public:
	Block** arr;
	std::list<Entity*>  Enemies;//список врагов.
	std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка
	
	Game();
	~Game();
	void InitEnemies(sf::Image* Image);
	Block** getMap();
};

