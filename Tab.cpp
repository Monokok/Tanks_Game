#include "Tab.h"
using namespace sf;



Tab:: Tab(sf::String File, float w, float h)
{
	showTab = 0;
	Timer = 0;
	playerRKitString << 0;

	image.loadFromFile("images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
	sprite.setPosition(view.getCenter().x, view.getCenter().y);

	font.loadFromFile("fonts/Bemount.otf");
	RKits.setFont(font);
	RKits.setCharacterSize(20);
	RKits.setString(sf::String(L"Подобрано ремкомплектов:") + playerRKitString.str());
	//RKits.setStyle(sf::Text::Bold);

	HP.setFont(font);
	HP.setCharacterSize(20);
	HP.setString(L"HP:" + playerHPString.str());

	Time.setFont(font);
	Time.setCharacterSize(20);
	Time.setString(L"Общее время:" + playerTimeString.str());

	sf::Vector2f targetSize(210.0f, 80.0f); //целевой размер

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
}
void Tab::SetRKits(int value)
{
	playerRKitString.str("");
	playerRKitString << value;
	RKits.setString(L"Подобрано ремкомплектов:" + playerRKitString.str());
}
void Tab::SetPos(float x, float y)
{
	y -= 230;

	HP.setPosition(x, y - 30);
	Time.setPosition(x, y - 15);
	RKits.setPosition(x, y);
	sprite.setPosition(x - 5, y - 40);

}
sf::Text Tab::returnRKits()
{
	return RKits;
}

void Tab::SetHP(int value)
{
	playerHPString.str("");
	playerHPString << value;
	HP.setString(L"HP:" + playerHPString.str());
}

sf::Text Tab::returnHP()
{
	return HP;
}

void Tab::SetTime(int value)
{
	Timer = value; //
	playerTimeString.str("");
	playerTimeString << Timer;
	Time.setString(L"Общее время (сек) :" + playerTimeString.str());
}

sf::Text Tab::returnTime()
{
	return Time;
}

bool Tab::GetShowTab()
{
	return showTab;
}

void Tab::SetShowTab(bool value)
{
	showTab = value;
}

sf::Sprite Tab::returnSprite()
{
	return sprite;
}
