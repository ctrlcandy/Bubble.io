/*!	\file Bubbleio.cpp
*   \brief File includes implementation of Bubbleio.h
*/

#include "Bubbleio.h"

void Bubbleio::play() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bubble.io", sf::Style::None);
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f));
	play(window, view);
}

void Bubbleio::play(sf::RenderWindow& window, sf::View& view) {
	Menu m;
	m.drawMenu(window, view);
	Game g;
	g.drawGame(window, view);
}