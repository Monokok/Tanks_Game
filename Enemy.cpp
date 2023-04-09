#include "Enemy.h"


Enemy::Enemy(sf::Image* File, sf::String name, float x, float y, float w, float h) /*Enemy(sf::String File, float x, float y, float w, float h)*/
{
	ID = rand() % 1000;
	speed = 0.09;
	sprite.setOrigin(w / 2, h / 2);
	dir = rand() % 4;
	if (dir == 0)
	{
		dx = speed;//�����
		dy = 0;
		sprite.setRotation(180);
	}
	if (dir == 1)
	{
		dx = -speed;//����
		dy = 0;
		//sprite.setRotation(-sprite.getRotation());
	}
	if (dir == 2)
	{
		dx = 0;//�����
		dy = -speed;
	}
	if (dir == 3)
	{
		dx = 0;//����
		dy = speed;
	}


	//dx = 0; dy = 0; 

	this->name = name;
	//this->File = File;//��� �����+����������
	this->w = w; this->h = h;//������ � ������
	//image.loadFromFile("images/" + File);//���������� � image ���� �����������\\ ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
	//image.createMaskFromColor(sf::Color(41, 33, 59));//������� �������� �����-����� ����
	texture.loadFromImage(*File);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	this->x = x; this->y = y;//���������� ��������� �������

	sprite.setTextureRect(
		sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
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
	sf::Vector2f targetSize(100.0f, 100.0f); //������� ������
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
	case 0: //������������ � other
		//��� ����� ������� �� ��� ������� Entity ������ ������ �����
		if ((other->getRectS().intersects(this->getRect()))) other->SetDir(-(other->GetDir()));

		break;
	case 1: //��������� �������� ��� ������������ 
		//
		//std::cout << typeid(other).name() << std::endl;
		//std::cout << other->GetString() << std::endl;
		//if (typeid(other).name() == "MyTank") //��������� � ��������� ������
		if ((other->GetString() == "Hero") || (other->GetString() == "Bullet"))
		{
			//!! ������� ����������� �� ����������� ����� �����
			//! ������� ������� "�������" � ������������� � ��������� �����
			switch (dir)
			{
			case 1: // dir = 0 - ������
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
			
			this->ReduceHP(20); //������� 20 ��������

			//std::cout << this->hp << "����:" << std::endl;
			//std::cout << this->hp << "�����:" << std::endl;
	//case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	//case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	//case 2: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	//case 3: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����

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

	switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case 2: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	case 3: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	}
	/*std::cout << "Enemy X: " << x << "Enemy Y: " << y << std::endl;*/
	int i = x / 100;
	int j = y / 100;

	//int rWay = 100 * (rand() % 5); //���� ������ �������� - ���� ������ �����������
	////���������� � ������� �.�. �������: Kx. ����������� = Tx
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
		//������ 23.03.23 � ���������� � ���������� �������
		if ((dy > 0) && (TileMap[i][j + 1] == '0') && (y > (j + 1) * 100 - 30)) this->ProcEvent(this, 3);//speed = -speed;
		else if (((dy < 0) && TileMap[i][j - 1] == '0') && (y < (j - 1) * 100 + 100 + 30)) this->ProcEvent(this, 3);//speed = -speed;
		else if (((dx > 0) && TileMap[i + 1][j] == '0') && (x > (i + 1) * 100 - 30)) this->ProcEvent(this, 3);//speed = -speed;
		else if (((dx < 0) && TileMap[i - 1][j] == '0') && (x < (i - 1) * 100 + 100 + 30)) this->ProcEvent(this, 3);//speed = -speed;
	}


	//if ((j > 0) && (j < HEIGHT_MAP - 1) && (i > 0) && (i < WIDTH_MAP - 1)) //���� �� ������ �����:
	//{

	//	//int rDir = rand() % 8;

	//	//switch (rDir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	//	//{
	//	//case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	//	//case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	//	//case 2: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	//	//case 3: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	//	//}
	//	//������ ���� �������: TileMap[j + 1][i]
	//	if ((TileMap[j + 1][i] == '0') && (y > (j + 1) * 100 - 30))
	//	{
	//		
	//		y = (j + 1) * 100 - 30; //-20 ������ �����������, ��� ��� �������� �� ������ ������ ������� ������ i � j ��������.
	//		dx = -dx;
	//		dy = -dy;
	//		//sprite.setRotation(360);
	//		
	//	}


	//	//������ ���� �������: TileMap[j - 1][i]
	//	else if ((TileMap[j - 1][i] == '0') && (y < (j - 1) * 100 + 100 + 30))
	//	{
	//		y = (j - 1) * 100 + 100 + 30;
	//		dx = -dx;
	//		dy = -dy;
	//		//sprite.setRotation(180);
	//		
	//	}

	//	//������ ������ �������: TileMap[j][i + 1]
	//	//std::cout << TileMap[j][i + 1] << std::endl; //� Y
	//	else if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30))
	//	{
	//		x = (i + 1) * 100 - 30;
	//		dx = -dx;
	//		dy = -dy;
	//		//sprite.setRotation(-90);
	//	}
	//	//if ((TileMap[j][i + 1] == '0') && (x > (i + 1) * 100 - 30)) x = (i + 1) * 100 - 30;

	//	//������ ����� �������: TileMap[j][i - 1]
	//	else if ((TileMap[j][i - 1] == '0') && (x < (i - 1) * 100 + 100 + 30))
	//	{
	//		x = (i - 1) * 100 + 100 + 30;
	//		dx = -dx;
	//		dy = -dy;
	//		/*sprite.setRotation(90);*/

	//	}

	//}
	if (dx > 0) //���� ��� ������
		sprite.setRotation(90);
	else if (dx < 0) sprite.setRotation(-90);
	if (dy > 0) sprite.setRotation(180);//����
	else if (dy < 0) sprite.setRotation(360);//�����

	x += dx * time;
	y += dy * time;

	sprite.setPosition(x, y); //������ ������� ������� � ����� ��� ������

	//checkCollisionWithMap(dx, dy, i, j);//������������ ������������ �� �
	//dir = rand() % 4;
	//float amount = int(100 * (rand() % 4)); //100 * ���-�� = ������� ������ ������
	//float coordX = x + amount; //���������� ���� ������ �������
	//float Tx = x;
	//float Ty = y;
	//
	//if (dir == 0)
	//{
	//	while (Tx < coordX)
	//	{
	//		dx = 0.01;
	//		dy = 0;
	//		this->x += dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
	//		Tx += dx * time;
	//	}
	//}
	//if (dir == 1)
	//{
	//	while (x != x - amount)
	//	{
	//		dx = -0.1;
	//		dy = 0;
	//		this->x += dx * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
	//	}
	//}
	//if (dir == 2)
	//{
	//	while (y != y + amount)
	//	{
	//		dx = 0;
	//		dy = 0.1;
	//		this->y += dy* time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
	//	}
	//}
	//if (dir == 3)
	//{
	//	while (y != y - amount)
	//	{
	//		dx = 0;
	//		dy = -1.0;
	//		this->y += dy * time;//��������� �� ����� = �������� ��������� � ��� ��������� ��������
	//	}
	//}

	if (hp <= 0) {
		life = false;
	}
	//sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ����� � ���� �������, ����� �� ��� ������ ����� �� �����.

}

