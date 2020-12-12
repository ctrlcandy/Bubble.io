/*!	\file Bubble.cpp
*   \brief File includes declaration of functions that
	responsible for displaying the menu
*/

#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
	float SCREEN_WIDTH = 1920;
	float SCREEN_HEIGHT = 1080;

public:
	Menu() {};
	void drawMenu(sf::RenderWindow& window, sf::View& view);
};


