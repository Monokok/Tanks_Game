
#pragma once
#include <SFML/Graphics.hpp>

sf::View view;

sf::View GetCoordinateForView(float x, float y) //ф-ция для считывания координат игрока
{
	float tempX = x; float tempY = y;

	if (x < 480) tempX = 480;//убираем левую полосу
	if (y < 270) tempY = 270;//убираем верхнюю полосу


	view.setCenter(tempX, tempY);
	return view;//возврат камеры = её обновление
}

sf::View ChangeView()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		view.setSize(1920, 1080);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		view.setSize(960, 540);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		view.zoom(1.0100f); //масштабируем, уменьшение
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}
	return view;
}