#include "Game.h"


void Game::InitEnemies(sf::Image* Image)
{
	srand(time(NULL));
	int rX;
	int rY;
	//Rand ����� � ������� ����� ��������� �����
	for (auto i = 0; i < AOE; )
	{
		rX = ((rand() % 1000) / 100);
		rY = ((rand() % 1000) / 100);
		if ((rX < HEIGHT_MAP) && (rY < WIDTH_MAP))
		{
			if ((TileMap[rX][rY] == ' '))  // ���� � ����� �� ���������� ������� ��������� ������ (' ') - �� ����� ��� ����� ���������� �����
			{
				
					i++;
					//Enemies.push_back(new Enemies(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 200, 97));//� ���������� � ������ ���� ����� ������ � �����
					Enemies.push_back(new Enemy(&(*Image), "T1", float(rX) * 100 + 50, float(rY) * 100 + 50, 200.0, 200.0)); // ����������������� ������ ����� - � ���� ����� ���������� - ����� �� ������); //���������
					//std::cout << "Rx: " << rX << " Ry: " << rY << "X: "<< cashX * 100 << " Y: " << cashY * 100 << std::endl;
				    //Enemies.push_back(new Block("RepairKit600.png", "Repair", rX * 100, rY * 100, 600, 600, 0)); //����������� = R
			}
		}
	}
}

Block** Game::getMap()
{
	return arr;
}

Game::Game()
{
	arr = new Block*[HEIGHT_MAP];
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		arr[i] = new Block[WIDTH_MAP];
	}//Block(sf::String File, sf::String type, float x, float y, float w, float h, bool solid);

	int count = 0;
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			//if (TileMap[i][j] == '0')
			//{
			//	WallImg.loadFromFile("images/brick_2.png");
			//	Wall Stena(&(*&WallImg), i * 100, j * 100, 626, 626, 1); //����� = 0
			//	/*std::vector<Map> v;
			//	for (int j = 0; j < WIDTH_MAP; j++) {
			//		v.push_back(Stena);
			//	}*/
			//	//
			//	arr[i][j] = Wall(&(*&WallImg), i * 100, j * 100, 626, 626, 1);// .push_back(v);
			//}
			if ((i == 0) || (j == 0) || (i == HEIGHT_MAP - 1) || (j == WIDTH_MAP - 1))
			{
				arr[i][j].set("brick_2.png", "Wall", i * 100, j * 100, 626, 626, 1); //����� = 0
			}
			else
			{
				if (TileMap[i][j] == '0') arr[i][j].set("brick_2.png", "Wall", i * 100, j * 100, 626, 626, 0); //����� = 0
				//if (TileMap[i][j] == 'R') arr[i][j].set("RepairKit600.png", "Repair", i * 100, j * 100, 600, 600, 0); //����������� = R

				if (TileMap[i][j] == ' ') arr[i][j].set("asphalt.png", "Road", i * 100, j * 100, 600, 600, 0); //������ = ' '
				if (TileMap[i][j] == 'w') arr[i][j].set("water.png", "Water", i * 100, j * 100, 600, 600, 0); //���� = w
				if (TileMap[i][j] == 'l') arr[i][j].set("listva.png", "Water", i * 100, j * 100, 600, 600, 0);; //������ = l
			}
		}
	}
}

Game::~Game()
{
	
}