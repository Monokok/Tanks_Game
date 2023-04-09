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
	bool life; //��� - �� ���
	float x, y;
	//sf::Vector2f oldpos; //��� ��������: ����� ����������� ������� ������� ������ ��� �����, ���� ��� �� ���������� � ���������
	float w, h, dx, dy, speed; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir; //����������� (direction) �������� ������
	sf::String File; //���� � �����������
	sf::Image image;//���� �����������
	sf::Texture texture;//���� ��������
	sf::Sprite sprite;//���� ������
	sf::String name;
public:
	sf::FloatRect GetGlobalBounds();
	int getID();
	//virtual void handle(const Event &event); //������� ��������� �������
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

