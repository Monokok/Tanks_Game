#pragma once
#include "Map.h"
#include "Enemy.h"

class Game
{
public:
	Block** arr;
	std::list<Entity*>  Enemies;//������ ������.
	std::list<Entity*>::iterator it;//�������� ����� ��������� �� ��-��� ������
	
	Game();
	~Game();
	void InitEnemies(sf::Image* Image);
	Block** getMap();
};

