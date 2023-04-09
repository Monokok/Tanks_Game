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
	this->File = File;//��� �����+����������
	this->w = w; this->h = h;//������ � ������
	image.loadFromFile("images/" + File);//���������� � image ���� �����������\\ ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
	//image.createMaskFromColor(sf::Color(41, 33, 59));//������� �������� �����-����� ����
	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	hp = 20;
	this->x = x; this->y = y;//���������� ��������� �������
	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������IntRect - ���������� �����

	sprite.setPosition(x, y);
	name = "Hero";
	sf::Vector2f targetSize(100.0f, 100.0f); //������� ������

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
	case 0: //������������ � other
		//��� ����� ������� �� ��� ������� Entity ������ ������ �����
		if ((other->getRectS().intersects(this->getRect()))) other->SetDir(-(other->GetDir()));

		break;
	case 1: //��������� ������� � ���� �������� �����
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
		//������� ���� ������ 95 <=> 79
		return sf::FloatRect(x - 48, y - 30, 79, 57);
		break;
	case 1:
		return sf::FloatRect(x - 48, y - 30, 79, 57); //������� ���� �����
		break;
	case 2:
		return sf::FloatRect(x - 30, y - 49, 57, 79); //������� ���� �����
		break;
	case 3:
		return sf::FloatRect(x - 30, y - 49, 57, 79); //���� ������� ����
		break;
	default:
		break;
	}
}

void MyTank::update(float time, Tab *pScore, Game* game) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
{
	int i = x / 100;
	int j = y / 100;
	if ((j > 0) && (j < WIDTH_MAP - 1) && (i > 0) && (i < HEIGHT_MAP - 1)) //���� �� ������ �����:
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
		case 2: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
		case 3: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
		}
		//std::cout << x / 100 << " " << y / 100 << std::endl;//(game->getMap()[(int)x/100][(int)y/100].GetString().toAnsiString()) << std::endl;
		//���� �� �����������, �� �������� ����������//������ ��� �� 9 ������ ������.

		/*for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{*/

		if ((game->getMap()[i + 1][j].GetString() == "Wall") && (game->getMap()[i + 1][j].GetGlobalBounds().intersects(getRectDir())) && dx > 0)
			//���� ������ ������ � �� � �� ��������
		{
			this->x -= dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
		}
		else if ((game->getMap()[i - 1][j].GetString() == "Wall") && (game->getMap()[i - 1][j].GetGlobalBounds().intersects(getRectDir())) && dx < 0)
		{
			this->x -= dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
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
		{//����� ����
			if (dx > 0) this->x -= dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
			else if (dy > 0) this->y -= dy * time;
		}
		else if ((game->getMap()[i - 1][j + 1].GetString() == "Wall") && (game->getMap()[i - 1][j + 1].GetGlobalBounds().intersects(getRectDir())))
		{//���� ����
			if (dx < 0) this->x -= dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
			else if (dy > 0) this->y -= dy * time;
		}
		else if ((game->getMap()[i + 1][j - 1].GetString() == "Wall") && (game->getMap()[i + 1][j - 1].GetGlobalBounds().intersects(getRectDir())))
		{//����� ����
			if (dx > 0) this->x -= dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
			else if (dy < 0) this->y -= dy * time;
		}
		else if ((game->getMap()[i - 1][j - 1].GetString() == "Wall") && (game->getMap()[i - 1][j - 1].GetGlobalBounds().intersects(getRectDir())))
		{//���� ����
			if (dx < 0) this->x -= dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
			else if (dy < 0) this->y -= dy * time;
		}
		else if (((game->getMap()[i][j].GetString() == "Road")))
		{
			if (game->getMap()[i][j].GetGlobalBounds().intersects(getRectDir()))
			{
				//std::cout << "Road" << std::endl;
			}
		}
		this->x += dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
		this->y += dy * time;//���������� �� y
		speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ����� � ���� �������, ����� �� ��� ������ ����� �� �����.


		if (hp > 0)
		{
			(*pScore).SetHP(hp); //���� ��� ���� - ���������� � ����� ���-�� HP
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
				dir = 1; speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������.
				sprite.setRotation(-90);
				GetCoordinateForView(x, y);
			}

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
				dir = 0; speed = 0.1;//����������� ������, �� ����
				sprite.setRotation(90);
				GetCoordinateForView(x, y);
			}

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
				dir = 3; speed = 0.1;//����������� ����, �� ����
				sprite.setRotation(180);
				GetCoordinateForView(x, y);
			}

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) { //���� ������ ������� ������� ����� ��� ���� ����� �
				dir = 2; speed = 0.1;//����������� �����, �� ����
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



void MyTank::interactionWithMap(Tab* pScore, Game* game)//�-��� �������������� � ������
{

	int i = x / 100;
	int j = y / 100;
	if ((j > 0) && (j < WIDTH_MAP - 1) && (i > 0) && (i < HEIGHT_MAP - 1)) //���� �� ������ �����:
	{

		//std::cout << "TileMap[i][j]: " << i << " " << j << std::endl;
		//������ ���� �������: TileMap[j + 1][i]
		//if ((TileMap[j + 1][i] == '0') && (y > (j + 1) * 100 - 30)) y = (j + 1) * 100 - 30; //-20 ������ �����������, ��� ��� �������� �� ������ ������ ������� ������ i � j ��������.
		//if ((dy > 0) &&(TileMap[i][j + 1] == '0') && (y > (j + 1) * 100 - 30)) y = (j + 1) * 100 - 30; //-20 ������ �����������, ��� ��� �������� �� ������ ������ ������� ������ i � j ��������.
		//if ((dy > 0) && (TileMap[i][j + 1] == '0') && (y > (j + 1) * 100 - 30)) speed = -speed; //-20 ������ �����������, ��� ��� �������� �� ������ ������ ������� ������ i � j ��������.
		

		//(game->getMap()[i][j].GetGlobalBounds().intersects(getRectDir())))

		//������ ���� �������: TileMap[j - 1][i]
		//else if ((TileMap[j - 1][i] == '0') && (y < (j - 1) * 100 + 100 + 30)) y = (j - 1) * 100 + 100 + 30;
		/*else if (((dy < 0) && TileMap[i][j - 1] == '0') && (y < (j - 1) * 100 + 100 + 30)) y = (j - 1) * 100 + 100 + 30;*/
		/*else if (((dy < 0) && TileMap[i][j - 1] == '0') && (y < (j - 1) * 100 + 100 + 30)) speed = -speed;*/
		

		//////������ ������ �������: TileMap[j][i + 1]
		//////std::cout << TileMap[j][i + 1] << std::endl; //� Y
		////else if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;
		/*else if (((dx > 0) && TileMap[i + 1][j] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;*/
		//else if (((dx > 0) && TileMap[i + 1][j] == '0') && (x > (i + 1) * 100 - 30)) speed = -speed;

		
		//////if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;

		//////������ ����� �������: TileMap[j][i - 1]
		////else if ((TileMap[j][i - 1] == '0') && (x < (i - 1) * 100 + 100 + 30)) x = (i - 1) * 100 + 100 + 30;
		/*else if (((dx < 0) && TileMap[i][j - 1] == '0') && (x < (i - 1) * 100 + 100 + 30)) x = (i - 1) * 100 ;*/
		/*else if (((dx < 0) && TileMap[i - 1][j] == '0') && (x < (i - 1) * 100 + 100 + 30)) speed = -speed;*/
		

		if ((TileMap[i][j] == 'R') && (hp < 100)) //���� � ����� ������ 100 �� - �� �� ����� ����� �����������
		{
			TileMap[i][j] = ' ';
			//Tanks.arr[i][j].set("asphalt.png", 0, 0, 600, 600, 0); ����������� 05.04.23
			RKits += 1;
			(*pScore).SetRKits(RKits);
			std::cout << "hp= " << hp << "Here is RepairKit: mas = " << TileMap[i][j] << std::endl;
			if (hp >= 80) hp = 100; else hp += 20;
			std::cout << "hp= " << hp << " " << x << " " << y << std::endl;
		}
	}
	//old:
	//if ((j > 0) && (j < HEIGHT_MAP - 1) && (i > 0) && (i < WIDTH_MAP - 1)) //���� �� ������ �����:
	//{
	//	//if (TileMap[(int(GetY()) / 100)][int(GetX()) / 100 - 1] == '0') //���� ����� �����
	//	//{
	//	//	//int saveLeftI = int(GetY()) / 100; int saveLeftJ = (int(GetX()) / 100) - 1; //�������� � i j ����� ����� ��������� �� ���
	//	//	int saveLeftI = x / 100; int saveLeftJ = y / 100 - 1; //�������� � i j ����� ����� ��������� �� ���
	//	//	/*std::cout << "I save left wall" << std::endl;
	//	//	std::cout << "Save I " << saveLeftI << std::endl;
	//	//	std::cout << "Save J " << saveLeftJ << std::endl;
	//	//	std::cout << "X of Save IJ: " << arr[saveLeftI][saveLeftJ].GetX() << std::endl;
	//	//	std::cout << "Y of Save IJ: " << arr[saveLeftI][saveLeftJ].GetY() << std::endl;*/

	//	//	int saveRightI;  int saveRightJ;


	//	//	//if (arr[int(MyTank.GetY()) / 100][int(MyTank.GetX()) / 100].getRect().intersects(MyTank.getRectS())) //���� �����-���� ������ ������������ � ������
	//	//	if (getRectS().intersects(arr[saveLeftI][saveLeftJ].getRect()))//(MyTank.getRect().intersects(arr[int(MyTank.GetY()) / 100][int(MyTank.GetX()) / 100].getRect()))//���� ������������� ������� ������� ������������ � �������
	//	//	{
	//	//		std::cout << "Stolknovenie" << std::endl;
	//	//		
	//	//		//std::cout << "x of Map[i][j]:" << arr[i][j].GetX() << std::endl;
	//	//		//std::cout << "my X:" << MyTank.GetX() << std::endl;
	//	//		//std::cout << "y of Map[i][j]:" << arr[i][j].GetY() << std::endl;
	//	//		//std::cout << "my Y:" << MyTank.GetY() << std::endl;
	//	//		if (getDx() < 0) //���� ��� ���� ��� ������
	//	//		{

	//	//			std::cout << "MyTank: x" << GetX() << "\n";//����� ������
	//	//			std::cout << "Map[i][j]: x" << arr[i][j].GetX() << "\n\n";//����� ������

	//	//			SetX(x); //����������� ��� �� ������ ����� (�������)

	//	//			std::cout << "new MyTank: x" << GetX() << "\n";//����� ������
	//	//			std::cout << "new Map[i][j]: x" << arr[i][j].GetX() << "\n\n";//����� ������
	//	//		}
	//	//		//if (MyTank.getDy() > 0) //���� ��� ���� Dy += ...
	//	//		//{

	//	//		//}

	//	//	}
	//	//}


	//	//std::cout << TileMap[j][i] << " x=" << x << " y=" << y << " i=" << i << " j=" << j << std::endl;
	//	// 
	//	//������ ���� �������: TileMap[j + 1][i]
	//	if ((TileMap[j + 1][i] == '0') && (y > (j + 1) * 100 - 30)) y = (j + 1) * 100 - 30; //-20 ������ �����������, ��� ��� �������� �� ������ ������ ������� ������ i � j ��������.
	//	

	//	//������ ���� �������: TileMap[j - 1][i]
	//	else if ((TileMap[j - 1][i] == '0') && (y < (j - 1) * 100 + 100 + 30)) y = (j - 1) * 100 + 100 + 30;

	//	//������ ������ �������: TileMap[j][i + 1]
	//	//std::cout << TileMap[j][i + 1] << std::endl; //� Y
	//	else if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;
	//	//if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;
	//	
	//	//������ ����� �������: TileMap[j][i - 1]
	//	else if ((TileMap[j][i - 1] == '0') && (x < (i - 1) * 100 + 100 + 30)) x = (i - 1) * 100 + 100 + 30;


	//	//	std::cout << x - 1 << " " << y << " " << i << " " << j << std::endl;
	//	if ((TileMap[j][i] == 'R') && (hp < 100)) //���� � ����� ������ 100 �� - �� �� ����� ����� �������
	//	{
	//		TileMap[j][i] = ' ';
	//		arr[j][i].set("asphalt.png", 0, 0, 600, 600, 0); //!!!������ ��� ������ ������� �����!!!
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
	//	//���� ������ ����� 's' (������)
	//	//	x = 300; y = 300;//�
	//	//	TileMap[i][j] = ' ';//������� ������
	//}
}

;


