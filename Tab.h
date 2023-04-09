#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "View.h"


class Tab
{
private:
	bool showTab; //����� ��� ������� ����

	sf::String File; //���� � �����������
	sf::Image image;//���� �����������
	sf::Texture texture;//���� ��������
	sf::Sprite sprite;//���� ������

	std::ostringstream playerRKitString;
	std::ostringstream playerHPString;
	std::ostringstream playerTimeString; //

	int Timer; //���������� ��� �������� ������ ������� ����

	sf::Font font;
	sf::Text RKits;
	sf::Text HP;
	sf::Text Time; //��������� ������ ������� ����
public:
	Tab(sf::String File, float w, float h);
	void SetRKits(int value);
	void SetPos(float x, float y);
	sf::Text returnRKits();
	void SetHP(int value);
	sf::Text returnHP();
	void SetTime(int value);
	sf::Text returnTime();
	bool GetShowTab();
	void SetShowTab(bool value);
	sf::Sprite returnSprite();
};


