#pragma once
#include "Entity.h"


class Block :
	public Entity
{
protected:
	bool solid; //���������
public:
	Block(sf::String File, sf::String type, float x, float y, float w, float h, bool solid);
	Block();
	void UpdateSetTextureRect(int Value1, int Value2, int j, int i);
	void set(sf::String File, sf::String name, float x, float y, float w, float h, bool solid);
	sf::Sprite ReturnSprite();
	sf::FloatRect getRect();
	void ProcEvent(Entity* other, PostCode Code) override;
	bool GetSolid();
	float GetX();
	float GetY();

	//	sprite.setTextureRect(sf::IntRect(0, 0, 600, 600)); //������ ������� ���� ������������� ��� ������ ������, � �� ���� �����. IntRect - ���������� �����
	//	
	//	sf::Vector2f targetSize(100.0f, 100.0f); //������� ������ // ���� ����� � ��������� ������������� �������
	//	sprite.setPosition(j * 100, i * 100);
	//	sprite.setScale(
	//		targetSize.x / sprite.getLocalBounds().width,
	//		targetSize.y / sprite.getLocalBounds().height);
	//}
};

