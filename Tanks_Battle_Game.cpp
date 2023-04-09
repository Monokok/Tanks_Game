#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include <stdlib.h>
#include "view.h"
#include <sstream>
#include <vector>
#include <list>
#include <time.h>
#include "Entity.h"
#include "MyTank.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Tab.h"
#include "Block.h"
#include "Game.h"

using namespace sf;

Tab Score("Tab.png", 595, 400);
sf::Image WallImg; //

//std::list<Entity*>  Enemies;//список врагов. Убрано в Game.h 05.04.23
//std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка





//class Wall:public Block
//{
//public:
//	//Image = WallImg;
//	Wall()
//	{
//
//	}
//	Wall(sf::Image *File, float x, float y, float w, float h, bool solid)
//	{
//		image = *File;
//		solid = 1; //твердый
//		texture.loadFromImage(*File);//закидываем наше изображение в текстуру
//		//texture.loadFromImage(WallImg);//закидываем наше изображение в текстуру
//		sprite.setTexture(texture);//заливаем спрайт текстурой
//		this->x = x;
//		this->y = y;
//		sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода. IntRect - приведение типа для коллизии
//
//		sf::Vector2f targetSize(100.0f, 100.0f); //целевой размер // изза этого и сбиваются прорисовочные пиксели
//
//		sprite.setScale(
//			targetSize.x / sprite.getLocalBounds().width,
//			targetSize.y / sprite.getLocalBounds().height);
//
//		// set the origin of the entity
//		//sprite.setOrigin(650, 650);
//
//		// retrieve the origin of the entity
//		//sf::Vector2f origin = sprite.getOrigin(); // = (10, 20)
//	}
//	~Wall()
//	{
//		std::cout << "Destructor For Wall" << std::endl;
//	}
//private:
//
//};



//std::vector<std::vector<Map>> arr;
//std::vector < std::vector <Map> > arr(HEIGHT_MAP, std::vector <Map>(WIDTH_MAP)); // Объявление вектора на n строк по m элементов
//std::vector < std::vector < Map>> arr;
//std::vector <Map> Karta;


//void ClassMap() убрано в Game.h 05.04.23
//{
//	arr = new Block * [HEIGHT_MAP];
//	for (int i = 0; i < HEIGHT_MAP; i++)
//	{
//		arr[i] = new Block[WIDTH_MAP];
//	}
//
//	for (int i = 0; i < HEIGHT_MAP; i++)
//	{
//		for (int j = 0; j < WIDTH_MAP; j++)
//		{
//			//if (TileMap[i][j] == '0')
//			//{
//			//	WallImg.loadFromFile("images/brick_2.png");
//			//	Wall Stena(&(*&WallImg), i * 100, j * 100, 626, 626, 1); //Стена = 0
//			//	/*std::vector<Map> v;
//			//	for (int j = 0; j < WIDTH_MAP; j++) {
//			//		v.push_back(Stena);
//			//	}*/
//			//	//
//			//	arr[i][j] = Wall(&(*&WallImg), i * 100, j * 100, 626, 626, 1);// .push_back(v);
//			//}
//			if (TileMap[i][j] == '0') arr[i][j].set("brick_2.png", i * 100, j * 100, 626, 626, 1); //Стена = 0
//			if (TileMap[i][j] == 'R') arr[i][j].set("RepairKit600.png", i * 100, j * 100, 600, 600, 0); //Ремкомлпект = R
//			if (TileMap[i][j] == ' ') arr[i][j].set("asphalt.png", i * 100, j * 100, 600, 600, 0); //Дорога = ' '
//			if (TileMap[i][j] == 'w') arr[i][j].set("water.png", i * 100, j * 100, 600, 600, 1); //Вода = w
//			if (TileMap[i][j] == 'l') arr[i][j].set("listva.png", i * 100, j * 100, 600, 600, 0);; //Листва = l
//		}
//	}
//
//
//
//	/*for (int i = 0; i < HEIGHT_MAP; i++)
//	{
//		delete[] arr[i];
//	}*/
//
//	//delete[] arr;
//}


//void InitEnemies(sf::Image* Image) //первоначальная инициализация расстановки врагов Убрано в Game.h 05.04.23
//{
//	srand(time(NULL));
//	int rX;
//	int rY;
//	//Rand точки в которых могут спавнится Враги
//	for (auto i = 0; i < AOE; )
//	{
//		rX = ((rand() % 1000) / 100);
//		rY = ((rand() % 1000) / 100);
//		if ((rX < HEIGHT_MAP) && (rY < WIDTH_MAP))
//		{
//			if ((TileMap[rX][rY] == ' '))  // если в карте по случайному индексу находится Дорога (' ') - то можно там будет заспавнить Врага
//			{
//				i++;
//				//Enemies.push_back(new Enemies(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 200, 97));//и закидываем в список всех наших врагов с карты
//				Enemies.push_back(new Enemy(&(*Image), float(rX) * 100 + 50, float(rY) * 100 + 50, 200.0, 200.0)); // переинициализирую нового врага - у него новые координаты - место на Дороге); //добавляем
//				//std::cout << "Rx: " << rX << " Ry: " << rY << "X: "<< cashX * 100 << " Y: " << cashY * 100 << std::endl;
//			}
//		}
//	}
//}






int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	Game Tanks;
	
	//image for enemies:
	sf::Image TankImage;
	TankImage.loadFromFile("images/tank200.png");
	
	
	//Wall stena(&WallImg, 2 * 100, 2 * 100, 626, 626, 1);
	/*MainWindow.draw(stena.ReturnSprite());*/
	//

	Tanks.InitEnemies(&TankImage);

	view.reset(sf::FloatRect(0, 0, 960, 540)); //обновление вида Камеры

	//ClassMap(); //заполняем карту на окне //перенесено в конструктор Game.h 05.04.23

	sf::RenderWindow MainWindow(sf::VideoMode(1920, 1080), "Tanks Battles", sf::Style::Default, settings);//класс - главное окно
	/*Block Foliage; убрано 05.04.23
	Foliage.set("listva.png", 0, 0, 600, 600, 0);*/


	/*Map Brick;
	Brick.set("brick_2.png", 0, 0, 626, 626, 1);

	Map Road;
	Road.set("asphalt.png", 0, 0, 600, 600, 0);

	

	Map Water;
	Water.set("water.png", 0, 0, 600, 600, 1);

	Map Repair;
	Repair.set("RepairKit600.png", 0, 0, 600, 600, 0);*/

	// Limit the framerate to 60 frames per second (this step is optional)
	//MainWindow.setFramerateLimit(120);

	sf::Clock clock; //привязываемся ко времени, а не к ЦП.
	sf::Clock LiveTimer;

	MyTank MyTank("tank200.png", 150, 150, 200.0, 200.0);
	
	while (MainWindow.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		if (MyTank.GetHP() > 0)
		{
			Score.SetTime(LiveTimer.getElapsedTime().asSeconds());
		}

		clock.restart();
		time = time / 800;//скорость игры

		sf::Event event;//Класс SFML событие
		while (MainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //Если закрыли окно:
				MainWindow.close();
			if (event.type == sf::Event::Resized)
			{
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
			}
			if (event.type == Event::KeyPressed)
			{//событие нажатия клавиши
				if ((event.key.code == Keyboard::Tab)) {//если клавиша ТАБ
					switch (Score.GetShowTab())
					{//переключатель, реагирующий на логическую переменную showMissionText

					case true: {
						Score.SetShowTab(false);
						break;
					}
					case false: {
						Score.SetShowTab(true);
						break;
					}
					}

				}
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Space" << std::endl;
					/*Tanks.Enemies.push_back(new Bullet(MyTank.GetX(), MyTank.GetY(), 512, 512, MyTank.GetDir(), 0, &Tanks));*/
					Tanks.Enemies.push_back(new Bullet(MyTank.GetX(), MyTank.GetY(), 512, 512, MyTank.GetDir(), 0, &Tanks, MyTank.getID()));
				}
			}
			

			/*if (event.type == sf::Event::MouseMoved)
			{
				std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
				std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
			}*/
		}
		MainWindow.clear(sf::Color(25, 25, 25));

		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{


				if (TileMap[i][j] == ' ') { //Cell.setTextureRect(IntRect(0, 0, 32, 32));
					Tanks.arr[i][j].UpdateSetTextureRect(600, 600, i, j);
					/*arr[i][j].sprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
					arr[i][j].sprite.setPosition(j * 100, i * 100);*/
					MainWindow.draw(Tanks.arr[i][j].ReturnSprite());
				}

				if (TileMap[i][j] == 'R')
				{
					Tanks.arr[i][j].UpdateSetTextureRect(600, 600, i, j);
					/*arr[i][j].sprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
					arr[i][j].sprite.setPosition(j * 100, i * 100);*/
					MainWindow.draw(Tanks.arr[i][j].ReturnSprite());
				}

				if (TileMap[i][j] == 'w')
				{
					Tanks.arr[i][j].UpdateSetTextureRect(600, 600, i, j);
					//arr[i][j].sprite.setTextureRect(sf::IntRect(0, 0, 600, 600)); //обновить прорисовку спрайта - UpdateSetTextureRect
					//arr[i][j].sprite.setPosition(j * 100, i * 100); //отрисовать на позиции

					MainWindow.draw(Tanks.arr[i][j].ReturnSprite());

				}
				if ((TileMap[i][j] == '0'))
				{
					Tanks.arr[i][j].UpdateSetTextureRect(626, 626, i, j);
					/*arr[i][j].sprite.setTextureRect(sf::IntRect(0, 0, 626, 626));
					arr[i][j].sprite.setPosition(j * 100, i * 100);*/
					MainWindow.draw(Tanks.arr[i][j].ReturnSprite());
				}
			}
		}

		MyTank.update(time, &Score, &Tanks); //for tank move: its method describes the keys and events when they are pressed

		for (Tanks.it = Tanks.Enemies.begin(); Tanks.it != Tanks.Enemies.end();)//from 1 to last list's entity
		{
			if ((*Tanks.it)->GetString() == "T1")
			{
				(*Tanks.it)->update(time);//updating enemies and bullets
				if ((*Tanks.it)->GetLife() == false) {
					//std::cout << "Before remove" << *it << std::endl;
					//std::cout << "BSize:" << Enemies.size() << std::endl;
					delete (*Tanks.it);

					Tanks.it = Tanks.Enemies.erase(Tanks.it); // если этот объект мертв, то удаляем его 
					
					//delete (*it); 
					//std::cout << "After remove" << *it << std::endl;
					//std::cout << "ASize:" << Enemies.size() << std::endl;
				}
				else Tanks.it++;//go to the next objects: (итератором) к след объекту.
			}
			else if ((*Tanks.it)->GetString() == "Bullet")
			{
				(*Tanks.it)->update(time, &Tanks.Enemies, &MyTank);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
				if ((*Tanks.it)->GetLife() == false) {
					//std::cout << "Before remove" << *it << std::endl;
					//std::cout << "BSize:" << Enemies.size() << std::endl;
					delete (*Tanks.it);
					Tanks.it = Tanks.Enemies.erase(Tanks.it); // если этот объект мертв, то удаляем его 

					//delete (*it); 
					//std::cout << "After remove" << *it << std::endl;
					//std::cout << "ASize:" << Enemies.size() << std::endl;
				}
				else Tanks.it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
			}
		}

		for (Tanks.it = Tanks.Enemies.begin(); Tanks.it != Tanks.Enemies.end(); Tanks.it++)
		{
			if ((*Tanks.it)->getRect().intersects(MyTank.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				if ((*Tanks.it)->GetString() == "T1")
				{
					//(*it)->SetLife(0);
					//
					(*Tanks.it)->ProcEvent(&MyTank, PostCode(1)); // отбрасывание с откусыванием части здоровья
				}
			}
		}
		
		/*if ((MyTank.sprite.getGlobalBounds().intersects(Brick.sprite.getGlobalBounds())) && Brick.solid)

		{
			std::cout << "Brick is coming" << std::endl;
			MyTank.sprite.setPosition(MyTank.oldpos);

		}

		else

		{

			MyTank.oldpos = MyTank.sprite.getPosition();

		};*/


		//MainWindow.draw(EnemyTank.sprite);

		for (Tanks.it = Tanks.Enemies.begin(); Tanks.it != Tanks.Enemies.end(); Tanks.it++) {
			MainWindow.draw((*Tanks.it)->ReturnSprite()); //drawing entities - enemy-tanks and bullets
		}

		

		MainWindow.draw(MyTank.ReturnSprite());
		

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
					if (TileMap[i][j] == 'l')
					{
						//Foliage.UpdateSetTextureRect(600, 600, i, j); убраны 2 строки 05.04.23
						// MainWindow.draw(Foliage.ReturnSprite());
						// 
						// 
						//Foliage.sprite.setTextureRect(sf::IntRect(0, 0, 600, 600));
						//Foliage.sprite.setPosition(j * 100, i * 100);
						
					}
			}

		if (Score.GetShowTab())
		{
			//Score.setTheString(L"Убито:");//задаем строку тексту
			//Score.setTheRKits();
			Score.SetPos(view.getCenter().x, view.getCenter().y);
			MainWindow.draw(Score.returnSprite());
			MainWindow.draw(Score.returnTime());
			MainWindow.draw(Score.returnRKits());
			MainWindow.draw(Score.returnHP());

		}
		ChangeView();
		MainWindow.setView(view);
		MainWindow.display();
	}

	return 0;
}

