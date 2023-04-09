#include "Bullet.h"


void Bullet::ProcEvent(Entity* other, PostCode Code)
{
	switch (Code.GetCode())
	{
	case 0: //столкновение снаряда с танком противника
		//if ((other->getRectS().intersects(this->getRect()))); //&other->SetLife(&other->GetLife() - 1);
		life = false;
 		(*other).ProcEvent(this, 1);
		break;
	case 1: //попадание снаряда в танк главного героя (уменьшение hp)
		//
		life = false;
		(*other).ProcEvent(this, 1); 
		break;
	default:
		break;
	}
}

Bullet::Bullet(float x, float y, int W, int H, int dir, bool AtMyTank, Game* game, int TankID)
{
	ID = TankID; //снаряд имеет ID'шник своего танка, что им выстрелил
	this->game = game;
	std::cout << "BulletConstr " << std::endl;
	this->AtMyTank = AtMyTank;
	this->x = x;
	this->y = y;
	this->dir = dir;
	speed = 0.3;
	this->w = W; this->h = H;
	hp = 1;
	life = true;
	image.loadFromFile("images/bullet.png");
	texture.loadFromImage(image);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой
	sprite.setOrigin(w / 2, h / 2);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	name = "Bullet";

	switch (dir)
	{
	case 0:
		dx = speed;
		dy = 0;
		sprite.setRotation(90);
		break;
	case 1:
		sprite.setRotation(-90);
		dx = -speed;
		dy = 0;
		break;
	case 2:
		sprite.setRotation(360);//вверх
		dx = 0;
		dy = -speed;
		break;
	case 3:
		sprite.setRotation(180);//вниз
		dx = 0;
		dy = speed;
		break;
	}

	//if (dx > 0) //если идём вправо
	//	sprite.setRotation(90);
	//else if (dx < 0) sprite.setRotation(-90);
	//if (dy > 0) sprite.setRotation(180);//вниз
	//else if (dy < 0) sprite.setRotation(360);//вверх

	sprite.setPosition(x, y);

	sf::Vector2f targetSize(10.0f, 10.0f); //целевой размер
	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
}

//	   2
//     ↑
//     |
//1 ←  0  -→ 0
//     |
//     ↓
//	   3

void Bullet::update(float time, std::list<Entity*>  *pEnemies, Entity* pMyTank)
{
	//std::cout << "Bullet X: " << x << "Bullet Y: " << y << std::endl;
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '0') //обработка столкновения со стеной
			{
				//if ((sf::FloatRect(x, y, 10, 10).intersects(*(game.arr[i][j].getRect()))))// 05.04.23
				if ((sf::FloatRect(x, y, 10, 10).intersects((*game).arr[i][j].getRect())))
				{
					ProcEvent(&(*game).arr[i][j], 0);
				}
			}
		}
	}

	x += dx * time;//само движение по х
	y += dy * time;//по у

	//if (x <= 0) x = 1;// задержка в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
	//if (y <= 0) y = 1;

 	if ((AtMyTank == 0) && (pEnemies != NULL))
	{
		std::list<Entity*>::iterator Yeah;//итератор чтобы проходить по эл-там списка
		for (Yeah = (*pEnemies).begin(); Yeah != (*pEnemies).end(); Yeah++)//проходимся по эл-там списка
		{
			if ((*Yeah)->getID() != ID)
			{
				//if (getRect().intersects((*Yeah)->getRect())) //если этот объект столкнулся с пулей,
				if (sf::FloatRect(x, y, 10, 10).intersects((*Yeah)->getRectS())) //если этот объект столкнулся с пулей, 
				{
					//(*Yeah)->ReduceHP(20);
					/*(*Yeah)->ProcEvent(this, 1);*/
					ProcEvent(*Yeah, 0);
					
					//ProcEvent(*Yeah, 1);
					//life = false;// то пуля умирает

				}
			}
		}
	}
	else
	{
		if (getRect().intersects((*pMyTank).getRect())) //если этот объект столкнулся с пулей,
		{
			//std::cout << "Penetration at MyTank!" << std::endl; убрано в procEvent 06.04.23
			//life = false;// то пуля умирает
			//(*pMyTank).ReduceHP(20);
			ProcEvent(pMyTank, 1);
		}
	}

	//sprite.setPosition(x + w / 2, y + h / 2);//задается позицию пуле
	sprite.setPosition(x, y);//задается позицию пуле

}
Bullet::~Bullet()
{
	//std::cout << "Bullet Destructor" << std::endl;
}
