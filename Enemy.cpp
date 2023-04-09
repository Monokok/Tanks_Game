#include "Enemy.h"


Enemy::Enemy(sf::Image* File, sf::String name, float x, float y, float w, float h) /*Enemy(sf::String File, float x, float y, float w, float h)*/
{
	ID = rand() % 1000;
	speed = 0.09;
	sprite.setOrigin(w / 2, h / 2);
	dir = rand() % 4;
	if (dir == 0)
	{
		dx = speed;//право
		dy = 0;
		sprite.setRotation(180);
	}
	if (dir == 1)
	{
		dx = -speed;//лево
		dy = 0;
		//sprite.setRotation(-sprite.getRotation());
	}
	if (dir == 2)
	{
		dx = 0;//вверх
		dy = -speed;
	}
	if (dir == 3)
	{
		dx = 0;//вниз
		dy = speed;
	}


	//dx = 0; dy = 0; 

	this->name = name;
	//this->File = File;//имя файла+расширение
	this->w = w; this->h = h;//высота и ширина
	//image.loadFromFile("images/" + File);//запихиваем в image наше изображение\\ вместо File мы передадим то, что пропишем при создании объекта. В случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
	//image.createMaskFromColor(sf::Color(41, 33, 59));//убираем ненужный темно-синий цвет
	texture.loadFromImage(*File);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой
	this->x = x; this->y = y;//координата появления спрайта

	sprite.setTextureRect(
		sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	sprite.setColor(sf::Color::Red);

	sprite.setPosition(x, y);
	if (name == "T1")
	{
		hp = 100;
	}
	else if (name == "T2")
	{
		hp = 200;
	}
	else if (name == "T3")
	{
		hp = 300;
	}
	
	life = true;
	sf::Vector2f targetSize(100.0f, 100.0f); //целевой размер
	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);



	// retrieve the origin of the entity
	//sf::Vector2f origin = sprite.getOrigin(); // = (10, 20)
}

void Enemy::ProcEvent(Entity* other, PostCode Code)
{
	switch (Code.GetCode())
	{
	case 0: //столкновение с other
		//тут метод который не даёт другому Entity пройти сквозь стену
		if ((other->getRectS().intersects(this->getRect()))) other->SetDir(-(other->GetDir()));

		break;
	case 1: //попадание снарядом или столкновение 
		//
		//std::cout << typeid(other).name() << std::endl;
		//std::cout << other->GetString() << std::endl;
		//if (typeid(other).name() == "MyTank") //сравнение с названием класса
		if ((other->GetString() == "Hero") || (other->GetString() == "Bullet"))
		{
			//!! сделать откидывание от направления моего танка
			//! Сделать функцию "МинусХП" с отбрасыванием и урезанием жизни
			switch (dir)
			{
			case 1: // dir = 0 - вправо
				//image.createMaskFromColor(sf::Color::Magenta);
				
				break;
			case 0:
				//image.createMaskFromColor(sf::Color::Magenta);
				
				break;
			case 2:
				//image.createMaskFromColor(sf::Color::Magenta);
				
				break;
			case 3:
				//image.createMaskFromColor(sf::Color::Magenta);
				
				break;

			default:
				break;
			}
			
			this->ReduceHP(20); //снимаем 20 здоровья

			//std::cout << this->hp << "Было:" << std::endl;
			//std::cout << this->hp << "Стало:" << std::endl;
	//case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	//case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	//case 2: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вверх
	//case 3: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вниз

		}
		break;
	case 3:
		this->speed = -(this->speed);
		break;
	default:
		break;
	}
}

void Enemy::update(float time, std::list<Entity*>  *pEnemies, Entity* pMyTank)
{

	switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case 2: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вверх
	case 3: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вниз
	}
	/*std::cout << "Enemy X: " << x << "Enemy Y: " << y << std::endl;*/
	int i = x / 100;
	int j = y / 100;

	//int rWay = 100 * (rand() % 5); //пять блоков проходит - пора менять направление
	////координата в которую д.б. попасть: Kx. Изначальная = Tx
	//float Tx = x;
	//float Kx = x + rWay;
	//float Ty = y;
	//float Ky = y + rWay;

	/*for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if ((getRectR().intersects(arr[i][j].getRect())))
				{
					dx = -dx;
					dy = -dy;
				}
			}
		}
	}*/

	if ((j > 0) && (j < WIDTH_MAP - 1) && (i > 0) && (i < HEIGHT_MAP - 1))
	{
		//убрано 23.03.23 и перенесено в обработчик событий
		if ((dy > 0) && (TileMap[i][j + 1] == '0') && (y > (j + 1) * 100 - 30)) this->ProcEvent(this, 3);//speed = -speed;
		else if (((dy < 0) && TileMap[i][j - 1] == '0') && (y < (j - 1) * 100 + 100 + 30)) this->ProcEvent(this, 3);//speed = -speed;
		else if (((dx > 0) && TileMap[i + 1][j] == '0') && (x > (i + 1) * 100 - 30)) this->ProcEvent(this, 3);//speed = -speed;
		else if (((dx < 0) && TileMap[i - 1][j] == '0') && (x < (i - 1) * 100 + 100 + 30)) this->ProcEvent(this, 3);//speed = -speed;
	}


	//if ((j > 0) && (j < HEIGHT_MAP - 1) && (i > 0) && (i < WIDTH_MAP - 1)) //если мы внутри карты:
	//{

	//	//int rDir = rand() % 8;

	//	//switch (rDir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	//	//{
	//	//case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	//	//case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	//	//case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	//	//case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	//	//}
	//	//Ячейка ниже текущей: TileMap[j + 1][i]
	//	if ((TileMap[j + 1][i] == '0') && (y > (j + 1) * 100 - 30))
	//	{
	//		
	//		y = (j + 1) * 100 - 30; //-20 делаем погрешность, ибо при переходе на нижнюю правую границу ячейки i и j меняются.
	//		dx = -dx;
	//		dy = -dy;
	//		//sprite.setRotation(360);
	//		
	//	}


	//	//Ячейка выше текущей: TileMap[j - 1][i]
	//	else if ((TileMap[j - 1][i] == '0') && (y < (j - 1) * 100 + 100 + 30))
	//	{
	//		y = (j - 1) * 100 + 100 + 30;
	//		dx = -dx;
	//		dy = -dy;
	//		//sprite.setRotation(180);
	//		
	//	}

	//	//Ячейка правее текущей: TileMap[j][i + 1]
	//	//std::cout << TileMap[j][i + 1] << std::endl; //и Y
	//	else if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30))
	//	{
	//		x = (i + 1) * 100 - 30;
	//		dx = -dx;
	//		dy = -dy;
	//		//sprite.setRotation(-90);
	//	}
	//	//if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;

	//	//Ячейка левее текущей: TileMap[j][i - 1]
	//	else if ((TileMap[j][i - 1] == '0') && (x < (i - 1) * 100 + 100 + 30))
	//	{
	//		x = (i - 1) * 100 + 100 + 30;
	//		dx = -dx;
	//		dy = -dy;
	//		/*sprite.setRotation(90);*/

	//	}

	//}
	if (dx > 0) //если идём вправо
		sprite.setRotation(90);
	else if (dx < 0) sprite.setRotation(-90);
	if (dy > 0) sprite.setRotation(180);//вниз
	else if (dy < 0) sprite.setRotation(360);//вверх

	x += dx * time;
	y += dy * time;

	sprite.setPosition(x, y); //задаем позицию спрайта в место его центра

	//checkCollisionWithMap(dx, dy, i, j);//обрабатываем столкновение по Х
	//dir = rand() % 4;
	//float amount = int(100 * (rand() % 4)); //100 * кол-во = сколько блоков пройдёт
	//float coordX = x + amount; //координата куда должен попасть
	//float Tx = x;
	//float Ty = y;
	//
	//if (dir == 0)
	//{
	//	while (Tx < coordX)
	//	{
	//		dx = 0.01;
	//		dy = 0;
	//		this->x += dx * time;//ускорение на время = смещение координат и как следствие движение
	//		Tx += dx * time;
	//	}
	//}
	//if (dir == 1)
	//{
	//	while (x != x - amount)
	//	{
	//		dx = -0.1;
	//		dy = 0;
	//		this->x += dx * time;//ускорение на время = смещение координат и как следствие движение
	//	}
	//}
	//if (dir == 2)
	//{
	//	while (y != y + amount)
	//	{
	//		dx = 0;
	//		dy = 0.1;
	//		this->y += dy* time;//ускорение на время = смещение координат и как следствие движение
	//	}
	//}
	//if (dir == 3)
	//{
	//	while (y != y - amount)
	//	{
	//		dx = 0;
	//		dy = -1.0;
	//		this->y += dy * time;//ускорение на время = смещение координат и как следствие движение
	//	}
	//}

	if (hp <= 0) {
		life = false;
	}
	//sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно вывод в этой функции, иначе бы наш спрайт стоял на месте.

}

