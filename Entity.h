#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include  "PostCode.h"

class Entity
{
protected:
	int hp;
	int ID;
	bool life; //жив - не жив
	float x, y;
	//sf::Vector2f oldpos; //для коллизии: будет дублировать позицию спрайта игрока все время, пока тот не столкнется с преградой
	float w, h, dx, dy, speed; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir; //направление (direction) движения игрока
	sf::String File; //файл с расширением
	sf::Image image;//сфмл изображение
	sf::Texture texture;//сфмл текстура
	sf::Sprite sprite;//сфмл спрайт
	sf::String name;
public:
	sf::FloatRect GetGlobalBounds();
	int getID();
	//virtual void handle(const Event &event); //функция обработки событий
	virtual void ProcEvent(Entity* other, PostCode Code) = 0;
	void SetDir(int dir);
	int GetDir();
	void ReduceHP(int value);
	virtual void update(float time, std::list<Entity*>  *pEnemies = nullptr, Entity* pMyTank = nullptr);
	sf::String GetString();
	void SetLife(int life);
	bool GetLife();
	virtual sf::FloatRect getRect();
	sf::FloatRect getRectR();
	sf::FloatRect getRectS();
	sf::Sprite ReturnSprite();
	void print();
	float GetX();
	void SetX(float x);
	float GetY();
	void SetY(float y);
	int GetHP();
	void SetHP(int hp);
};

