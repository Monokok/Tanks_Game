#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "View.h"


class Tab
{
private:
	bool showTab; //показ или скрытие таба

	sf::String File; //файл с расширением
	sf::Image image;//сфмл изображение
	sf::Texture texture;//сфмл текстура
	sf::Sprite sprite;//сфмл спрайт

	std::ostringstream playerRKitString;
	std::ostringstream playerHPString;
	std::ostringstream playerTimeString; //

	int Timer; //переменная для хранения общего времени игры

	sf::Font font;
	sf::Text RKits;
	sf::Text HP;
	sf::Text Time; //текстовый формат времени игры
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


