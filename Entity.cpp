#include "Entity.h"
#include <list>


void Entity::update(float time, std::list<Entity*>  *pEnemies, Entity* pMyTank)
{

}

int Entity::getID()
{
	return ID;
}

void Entity::SetDir(int dir)
{
	this->dir = dir;
}

//void Entity::handle(const Event& event)
//{
//}
int Entity::GetDir()
{
	return dir;
}
void Entity::ReduceHP(int value)
{
	hp -= value;
}
sf::String Entity::GetString()
{
	return name;
}
void Entity::SetLife(int life)
{
	this->life = life;
}
bool Entity::GetLife()
{
	return life;
}
sf::FloatRect Entity::getRect()
{
	return sf::FloatRect(x, y, 75, 75);
}

sf::FloatRect Entity::getRectR()
{
	return sf::FloatRect(x - 50, y - 50, 100, 100);
}

sf::FloatRect Entity::getRectS()
{
	return sf::FloatRect(x - 30, y - 30, 70, 70);	
}

sf::FloatRect Entity::GetGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

sf::Sprite Entity::ReturnSprite()
{
	return this->sprite;
}
void Entity::print()
{
	std::cout << x << " " << y << " " << hp << " " << std::endl;
}
float Entity::GetX()
{
	return x;
}
void Entity::SetX(float x)
{
	this->x = x;
}
float Entity::GetY()
{
	return y;
}
void Entity::SetY(float y)
{
	this->y = y;
}
int Entity::GetHP()
{
	return hp;
}
void Entity::SetHP(int hp)
{
	this->hp = hp;
}
/*void SetName(sf::String name)
{
	this->name = name;
}*/
