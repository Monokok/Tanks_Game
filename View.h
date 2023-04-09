
#pragma once
#include <SFML/Graphics.hpp>

sf::View view;

sf::View GetCoordinateForView(float x, float y) //�-��� ��� ���������� ��������� ������
{
	float tempX = x; float tempY = y;

	if (x < 480) tempX = 480;//������� ����� ������
	if (y < 270) tempY = 270;//������� ������� ������


	view.setCenter(tempX, tempY);
	return view;//������� ������ = � ����������
}

sf::View ChangeView()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		view.setSize(1920, 1080);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		view.setSize(960, 540);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		view.zoom(1.0100f); //������������, ����������
		//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}
	return view;
}