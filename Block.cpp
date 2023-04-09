#include "Block.h"
#include "Map.h"


Block::Block(sf::String File, sf::String name, float x, float y, float w, float h, bool solid)
{
	
	this->File = File;//��� �����+����������
	image.loadFromFile("images/" + File);//���������� � image ���� �����������\\ ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
	//image.createMaskFromColor(sf::Color(41, 33, 59));//������� �������� �����-����� ����
	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	this->x = x;
	this->y = y;
	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������, � �� ���� �����. IntRect - ���������� �����
	this->name = name;
	this->solid = solid;
	sf::Vector2f targetSize(100.0f, 100.0f); //������� ������ // ���� ����� � ��������� ������������� �������

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
	this->life = true;
	this->hp = 100; //��� 23.03.23
	dir = w = h = dx = dy = speed = 0;
	

	// set the origin of the entity
	//sprite.setOrigin(650, 650);

	// retrieve the origin of the entity
	//sf::Vector2f origin = sprite.getOrigin(); // = (10, 20)
}

Block::Block()
{
	File = "none.png";
	image.loadFromFile("images/none.png");//���������� � image ���� �����������\\ ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
	//image.createMaskFromColor(sf::Color(41, 33, 59));//������� �������� �����-����� ����
	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������, � �� ���� �����. IntRect - ���������� �����
	
	sf::Vector2f targetSize(100.0f, 100.0f); //������� ������ // ���� ����� � ��������� ������������� �������
	
	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
	this->hp = 100; //��� 23.03.23
	solid = false;
	life = true;
	x = 100; y = 100; name = "None";
	dir = w = h = dx = dy = speed = 0;
}

void Block::UpdateSetTextureRect(int Value1, int Value2, int j, int i)
{
	sprite.setTextureRect(sf::IntRect(0, 0, Value1, Value2));
	sprite.setPosition(j * 100, i * 100); //�������� i � j - ����� ���������� ����� ��� ����� ������ ��� ������. 
}

void Block::set(sf::String File, sf::String name, float x, float y, float w, float h, bool solid)
{

	this->File = File;//��� �����+����������
	image.loadFromFile("images/" + File);//���������� � image ���� �����������\\ ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
	//image.createMaskFromColor(sf::Color(41, 33, 59));//������� �������� �����-����� ����
	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	this->x = x;
	this->y = y;
	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������, � �� ���� �����. IntRect - ���������� �����

	//sprite.setOrigin(w / 2, h / 2);

	sf::Vector2f targetSize(100.0f, 100.0f); //������� ������ // ���� ����� � ��������� ������������� �������

	sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
	this->hp = 100; //��� 23.03.23
	this->solid = solid;
	life = true;
	this->name = name;

	// set the origin of the entity
	//sprite.setOrigin(650, 650);

	// retrieve the origin of the entity
	//sf::Vector2f origin = sprite.getOrigin(); // = (10, 20)
}

sf::Sprite Block::ReturnSprite()
{
	return this->sprite;
}

sf::FloatRect Block::getRect()
{

	return sf::FloatRect(x, y, 100, 100);

}

void Block::ProcEvent(Entity* other, PostCode Code)
{
	switch (Code.GetCode())
	{
	case 0: //������������ � other
		//��� ����� ������� �� ��� ������� Entity ������ ������ �����
		if ((other->getRectS().intersects(this->getRect())) && this->GetSolid()) other->SetDir(-(other->GetDir()));
		
		break;
	case 1: //��������� �������� � ����� (���������� hp)
		std::cout << x << " " << y << std::endl;
   		if ((other->GetString() == "Bullet") && solid == 0)
		{
 			this->ReduceHP(20);
			std::cout << hp << std::endl;
			//(TileMap[i][j] == '0') arr[i][j].set("brick_2.png", "Wall", i * 100, j * 100, 626, 626, 1); //����� = 0
 			if (hp < 0)
			{
				set("asphalt.png", "Road", x, y, 600, 600, 0);
				hp = 100;
				TileMap[(int)x / 100][(int)y / 100] = ' ';
			}
			//this->ReduceHP(1); //������� 20 ��������.
		}
		
		break;
	case 2: //�������� �����������
		if ((this->GetString() == "RepairKit") && (other->GetString() == "Hero"))
		{
			(*other).SetHP((*other).GetHP() + 20);
		}
		break;
	default:
		break;
	}
}

bool Block::GetSolid()
{
	return solid;
}

float Block::GetX()
{
	return x;
}
float Block::GetY()
{
	return y;
}

//	sprite.setTextureRect(sf::IntRect(0, 0, 600, 600)); //������ ������� ���� ������������� ��� ������ ������, � �� ���� �����. IntRect - ���������� �����
//	
//	sf::Vector2f targetSize(100.0f, 100.0f); //������� ������ // ���� ����� � ��������� ������������� �������
//	sprite.setPosition(j * 100, i * 100);
//	sprite.setScale(
//		targetSize.x / sprite.getLocalBounds().width,
//		targetSize.y / sprite.getLocalBounds().height);
//}
