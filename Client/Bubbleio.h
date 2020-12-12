/*!	\file Bubbleio.h
*   \brief File includes the declaration of methods that sequentially 
	call the menu and the game
	It is an abstraction over all classes of the Bubble.io game
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

class Bubbleio
{
	float SCREEN_WIDTH = 1920;
	float SCREEN_HEIGHT = 1080;

	void play(sf::RenderWindow& window, sf::View& view);

public:

	Bubbleio() {};
	void play();
};

