#include "MyTank.h"
#include "Block.h"
#include "Tab.h"


MyTank:: MyTank(sf::String File, float x, float y, float w, float h)
{
	ID = rand() % 1000;
	// set the origin of the entity
	sprite.setOrigin(w / 2, h / 2);
	score = 0;
	RKits = 0;
	dx = 0; dy = 0; speed = 0; dir = 0;
	this->File = File;//имя файла+расширение
	this->w = w; this->h = h;//высота и ширина
	image.loadFromFile("images/" + File);//запихиваем в image наше изображение\\ вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
	//image.createMaskFromColor(sf::Color(41, 33, 59));//убираем ненужный темно-синий цвет
	texture.loadFromImage(image);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой
	hp = 20;
	this->x = x; this->y = y;//координата появления спрайта
	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для выводаIntRect - приведение типов

	sprite.setPosition(x, y);
	name = "Hero";
	sf::Vector2f targetSize(100.0f, 100.0f); //целевой размер

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);


	// retrieve the origin of the entity
	//sf::Vector2f origin = sprite.getOrigin(); // = (10, 20)
}

void MyTank::ProcEvent(Entity* other, PostCode Code)
{
	switch (Code.GetCode())
	{
	case 0: //столкновение с other
		//тут метод который не даёт другому Entity пройти сквозь стену
		if ((other->getRectS().intersects(this->getRect()))) other->SetDir(-(other->GetDir()));

		break;
	case 1: //попадание снаряда в танк главного героя
		//ReduceHP(20);
		break;
	default:
		break;
	}
}

float MyTank::getDx()
{
	return dx;
}

float MyTank::getDy()
{
	return dy;
}

sf::FloatRect MyTank::getRectDir()
{
	switch (dir)
	{
	case 0:
		//смотрит танк вправо 95 <=> 79
		return sf::FloatRect(x - 48, y - 30, 79, 57);
		break;
	case 1:
		return sf::FloatRect(x - 48, y - 30, 79, 57); //смотрит танк влево
		break;
	case 2:
		return sf::FloatRect(x - 30, y - 49, 57, 79); //смотрит танк вверх
		break;
	case 3:
		return sf::FloatRect(x - 30, y - 49, 57, 79); //танк смотрит вниз
		break;
	default:
		break;
	}
}

void MyTank::update(float time, Tab *pScore, Game* game) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
{
	int i = x / 100;
	int j = y / 100;
	if ((j > 0) && (j < WIDTH_MAP - 1) && (i > 0) && (i < HEIGHT_MAP - 1)) //если мы внутри карты:
	{
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вверх
		case 3: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вниз
		}
		//std::cout << x / 100 << " " << y / 100 << std::endl;//(game->getMap()[(int)x/100][(int)y/100].GetString().toAnsiString()) << std::endl;
		//если не столкнулись, то изменяем координаты//сужаем фор до 9 блоков вокруг.

		/*for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{*/

		if ((game->getMap()[i + 1][j].GetString() == "Wall") && (game->getMap()[i + 1][j].GetGlobalBounds().intersects(getRectDir())) && dx > 0)
			//если справа стенка и мы в неё уперлись
		{
			this->x -= dx * time;//ускорение на время = смещение координат и как следствие движение
		}
		else if ((game->getMap()[i - 1][j].GetString() == "Wall") && (game->getMap()[i - 1][j].GetGlobalBounds().intersects(getRectDir())) && dx < 0)
		{
			this->x -= dx * time;//ускорение на время = смещение координат и как следствие движение
		}
		else if ((game->getMap()[i][j + 1].GetString() == "Wall") && (game->getMap()[i][j + 1].GetGlobalBounds().intersects(getRectDir())) && dy > 0)
		{
			this->y -= dy * time;
		}
		else if ((game->getMap()[i][j - 1].GetString() == "Wall") && (game->getMap()[i][j - 1].GetGlobalBounds().intersects(getRectDir())) && dy < 0)
		{
			this->y -= dy * time;
		}
		else if ((game->getMap()[i + 1][j + 1].GetString() == "Wall") && (game->getMap()[i + 1][j + 1].GetGlobalBounds().intersects(getRectDir())))
		{//право ниже
			if (dx > 0) this->x -= dx * time;//ускорение на время = смещение координат и как следствие движение
			else if (dy > 0) this->y -= dy * time;
		}
		else if ((game->getMap()[i - 1][j + 1].GetString() == "Wall") && (game->getMap()[i - 1][j + 1].GetGlobalBounds().intersects(getRectDir())))
		{//лево ниже
			if (dx < 0) this->x -= dx * time;//ускорение на время = смещение координат и как следствие движение
			else if (dy > 0) this->y -= dy * time;
		}
		else if ((game->getMap()[i + 1][j - 1].GetString() == "Wall") && (game->getMap()[i + 1][j - 1].GetGlobalBounds().intersects(getRectDir())))
		{//право выше
			if (dx > 0) this->x -= dx * time;//ускорение на время = смещение координат и как следствие движение
			else if (dy < 0) this->y -= dy * time;
		}
		else if ((game->getMap()[i - 1][j - 1].GetString() == "Wall") && (game->getMap()[i - 1][j - 1].GetGlobalBounds().intersects(getRectDir())))
		{//лево выше
			if (dx < 0) this->x -= dx * time;//ускорение на время = смещение координат и как следствие движение
			else if (dy < 0) this->y -= dy * time;
		}
		else if (((game->getMap()[i][j].GetString() == "Road")))
		{
			if (game->getMap()[i][j].GetGlobalBounds().intersects(getRectDir()))
			{
				//std::cout << "Road" << std::endl;
			}
		}
		this->x += dx * time;//ускорение на время = смещение координат и как следствие движение
		this->y += dy * time;//аналогично по y
		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y); //выводим спрайт в позицию x y , посередине. бесконечно вывод в этой функции, иначе бы наш спрайт стоял на месте.


		if (hp > 0)
		{
			(*pScore).SetHP(hp); //если ещё живы - отправляем в табло кол-во HP
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
				dir = 1; speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения.
				sprite.setRotation(-90);
				GetCoordinateForView(x, y);
			}

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
				dir = 0; speed = 0.1;//направление вправо, см выше
				sprite.setRotation(90);
				GetCoordinateForView(x, y);
			}

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
				dir = 3; speed = 0.1;//направление вниз, см выше
				sprite.setRotation(180);
				GetCoordinateForView(x, y);
			}

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) { //если нажата клавиша стрелка влево или англ буква А
				dir = 2; speed = 0.1;//направление вверх, см выше
				sprite.setRotation(360);
				GetCoordinateForView(x, y);
			}
		}
	}

	//interactionWithMap(pScore, game);
}

int MyTank::getPlayerRKit()
{
	return RKits;
}

int MyTank::getPlayerHP()
{
	return hp;
}



void MyTank::interactionWithMap(Tab* pScore, Game* game)//ф-ция взаимодействия с картой
{

	int i = x / 100;
	int j = y / 100;
	if ((j > 0) && (j < WIDTH_MAP - 1) && (i > 0) && (i < HEIGHT_MAP - 1)) //если мы внутри карты:
	{

		//std::cout << "TileMap[i][j]: " << i << " " << j << std::endl;
		//Ячейка ниже текущей: TileMap[j + 1][i]
		//if ((TileMap[j + 1][i] == '0') && (y > (j + 1) * 100 - 30)) y = (j + 1) * 100 - 30; //-20 делаем погрешность, ибо при переходе на нижнюю правую границу ячейки i и j меняются.
		//if ((dy > 0) &&(TileMap[i][j + 1] == '0') && (y > (j + 1) * 100 - 30)) y = (j + 1) * 100 - 30; //-20 делаем погрешность, ибо при переходе на нижнюю правую границу ячейки i и j меняются.
		//if ((dy > 0) && (TileMap[i][j + 1] == '0') && (y > (j + 1) * 100 - 30)) speed = -speed; //-20 делаем погрешность, ибо при переходе на нижнюю правую границу ячейки i и j меняются.
		

		//(game->getMap()[i][j].GetGlobalBounds().intersects(getRectDir())))

		//Ячейка выше текущей: TileMap[j - 1][i]
		//else if ((TileMap[j - 1][i] == '0') && (y < (j - 1) * 100 + 100 + 30)) y = (j - 1) * 100 + 100 + 30;
		/*else if (((dy < 0) && TileMap[i][j - 1] == '0') && (y < (j - 1) * 100 + 100 + 30)) y = (j - 1) * 100 + 100 + 30;*/
		/*else if (((dy < 0) && TileMap[i][j - 1] == '0') && (y < (j - 1) * 100 + 100 + 30)) speed = -speed;*/
		

		//////Ячейка правее текущей: TileMap[j][i + 1]
		//////std::cout << TileMap[j][i + 1] << std::endl; //и Y
		////else if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;
		/*else if (((dx > 0) && TileMap[i + 1][j] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;*/
		//else if (((dx > 0) && TileMap[i + 1][j] == '0') && (x > (i + 1) * 100 - 30)) speed = -speed;

		
		//////if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;

		//////Ячейка левее текущей: TileMap[j][i - 1]
		////else if ((TileMap[j][i - 1] == '0') && (x < (i - 1) * 100 + 100 + 30)) x = (i - 1) * 100 + 100 + 30;
		/*else if (((dx < 0) && TileMap[i][j - 1] == '0') && (x < (i - 1) * 100 + 100 + 30)) x = (i - 1) * 100 ;*/
		/*else if (((dx < 0) && TileMap[i - 1][j] == '0') && (x < (i - 1) * 100 + 100 + 30)) speed = -speed;*/
		

		if ((TileMap[i][j] == 'R') && (hp < 100)) //если у танка меньше 100 хп - то он может брать ремкоплекты
		{
			TileMap[i][j] = ' ';
			//Tanks.arr[i][j].set("asphalt.png", 0, 0, 600, 600, 0); закоменчено 05.04.23
			RKits += 1;
			(*pScore).SetRKits(RKits);
			std::cout << "hp= " << hp << "Here is RepairKit: mas = " << TileMap[i][j] << std::endl;
			if (hp >= 80) hp = 100; else hp += 20;
			std::cout << "hp= " << hp << " " << x << " " << y << std::endl;
		}
	}
	//old:
	//if ((j > 0) && (j < HEIGHT_MAP - 1) && (i > 0) && (i < WIDTH_MAP - 1)) //если мы внутри карты:
	//{
	//	//if (TileMap[(int(GetY()) / 100)][int(GetX()) / 100 - 1] == '0') //если слева стена
	//	//{
	//	//	//int saveLeftI = int(GetY()) / 100; int saveLeftJ = (int(GetX()) / 100) - 1; //сохраняю её i j чтобы потом обратится по ним
	//	//	int saveLeftI = x / 100; int saveLeftJ = y / 100 - 1; //сохраняю её i j чтобы потом обратится по ним
	//	//	/*std::cout << "I save left wall" << std::endl;
	//	//	std::cout << "Save I " << saveLeftI << std::endl;
	//	//	std::cout << "Save J " << saveLeftJ << std::endl;
	//	//	std::cout << "X of Save IJ: " << arr[saveLeftI][saveLeftJ].GetX() << std::endl;
	//	//	std::cout << "Y of Save IJ: " << arr[saveLeftI][saveLeftJ].GetY() << std::endl;*/

	//	//	int saveRightI;  int saveRightJ;


	//	//	//if (arr[int(MyTank.GetY()) / 100][int(MyTank.GetX()) / 100].getRect().intersects(MyTank.getRectS())) //если какая-либо ячейка пересекается с танком
	//	//	if (getRectS().intersects(arr[saveLeftI][saveLeftJ].getRect()))//(MyTank.getRect().intersects(arr[int(MyTank.GetY()) / 100][int(MyTank.GetX()) / 100].getRect()))//если прямоугольник спрайта объекта пересекается с игроком
	//	//	{
	//	//		std::cout << "Stolknovenie" << std::endl;
	//	//		
	//	//		//std::cout << "x of Map[i][j]:" << arr[i][j].GetX() << std::endl;
	//	//		//std::cout << "my X:" << MyTank.GetX() << std::endl;
	//	//		//std::cout << "y of Map[i][j]:" << arr[i][j].GetY() << std::endl;
	//	//		//std::cout << "my Y:" << MyTank.GetY() << std::endl;
	//	//		if (getDx() < 0) //если Мой танк идёт вправо
	//	//		{

	//	//			std::cout << "MyTank: x" << GetX() << "\n";//коорд игрока
	//	//			std::cout << "Map[i][j]: x" << arr[i][j].GetX() << "\n\n";//коорд Ячейки

	//	//			SetX(x); //отталкиваем его от стенки влево (впритык)

	//	//			std::cout << "new MyTank: x" << GetX() << "\n";//коорд игрока
	//	//			std::cout << "new Map[i][j]: x" << arr[i][j].GetX() << "\n\n";//коорд Ячейки
	//	//		}
	//	//		//if (MyTank.getDy() > 0) //если иду вниз Dy += ...
	//	//		//{

	//	//		//}

	//	//	}
	//	//}


	//	//std::cout << TileMap[j][i] << " x=" << x << " y=" << y << " i=" << i << " j=" << j << std::endl;
	//	// 
	//	//Ячейка ниже текущей: TileMap[j + 1][i]
	//	if ((TileMap[j + 1][i] == '0') && (y > (j + 1) * 100 - 30)) y = (j + 1) * 100 - 30; //-20 делаем погрешность, ибо при переходе на нижнюю правую границу ячейки i и j меняются.
	//	

	//	//Ячейка выше текущей: TileMap[j - 1][i]
	//	else if ((TileMap[j - 1][i] == '0') && (y < (j - 1) * 100 + 100 + 30)) y = (j - 1) * 100 + 100 + 30;

	//	//Ячейка правее текущей: TileMap[j][i + 1]
	//	//std::cout << TileMap[j][i + 1] << std::endl; //и Y
	//	else if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;
	//	//if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;
	//	
	//	//Ячейка левее текущей: TileMap[j][i - 1]
	//	else if ((TileMap[j][i - 1] == '0') && (x < (i - 1) * 100 + 100 + 30)) x = (i - 1) * 100 + 100 + 30;


	//	//	std::cout << x - 1 << " " << y << " " << i << " " << j << std::endl;
	//	if ((TileMap[j][i] == 'R') && (hp < 100)) //если у танка меньше 100 хп - то он может брать аптечки
	//	{
	//		TileMap[j][i] = ' ';
	//		arr[j][i].set("asphalt.png", 0, 0, 600, 600, 0); //!!!Убрать для работы подбора ремок!!!
	//		// 



	//		
	//			//set("water.png", 0, 0, 600, 600, 0);
	//		//ClassMap();
	//		//MainWindow.draw(arr[i][j].sprite);

	//		RKits += 1;
	//		Score.SetRKits(RKits);
	//		std::cout << "hp= " << hp << "Here is RepairKit: mas = " << TileMap[j][i] << std::endl;
	//		if (hp >= 80) hp = 100; else hp += 20;
	//		std::cout << "hp= " << hp << " " << x << " " << y << std::endl;
	//	}
	//	//если символ равен 's' (камень)
	//	//	x = 300; y = 300;//к
	//	//	TileMap[i][j] = ' ';//убираем камень
	//}
}

;


