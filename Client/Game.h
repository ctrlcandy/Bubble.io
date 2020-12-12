/*!	\file Bubble.cpp
*   \brief File includes declaration of functions that
	responsible for displaying the game
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Bubble.h"
#include "Feed.h"
#include "Client.h"

#include <string>
#include <cmath>
#include <limits>
#include <thread>

class Game
{
	float SCREEN_WIDTH = 1920;
	float SCREEN_HEIGHT = 1080;
	std::vector<Bubble> users;

	bool firstScreenCheck = false;
	bool secondScreenCheck = false;
	bool thirdScreenCheck = false;

	std::size_t scorePositionX = 480;
	std::size_t scoreCountY = 270;

	void update(Bubble& bubble, Feed& feed, std::vector<std::pair<std::size_t, sf::Vector2f>>& newFeedPositions);
	void setUserView(const Bubble& bubble, sf::View& view, sf::Text& scoreCount);
	void end(sf::RenderWindow& window, sf::View& view, sf::Text endText);

public:

	Game() {};
	void drawGame(sf::RenderWindow& window, sf::View& view);
};

