/*!	\file Bubble.cpp
*   \brief File includes implementation of Menu.h
*/

#include "Menu.h"

void Menu::drawMenu(sf::RenderWindow& window, sf::View& view) {
	sf::Event event;

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(SCREEN_WIDTH*2, SCREEN_HEIGHT*2));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(-SCREEN_WIDTH, -SCREEN_HEIGHT);

	sf::Texture rectangleTexture;
	const sf::Texture* pBRT = &rectangleTexture;
	rectangleTexture.loadFromFile("Textures/blurBackground.png");
	rectangle.setTexture(pBRT, true);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	sf::Text start;
	start.setFillColor(sf::Color::White);
	start.setOutlineColor(sf::Color::Black);
	start.setOutlineThickness(1);
	start.setFont(font);
	start.setCharacterSize(72);
	start.setPosition(-240, -60);
	start.setString("START GAME");

	sf::Text logo;
	logo.setFillColor(sf::Color::Magenta);
	logo.setOutlineColor(sf::Color::Yellow);
	logo.setOutlineThickness(3);
	logo.setFont(font);
	logo.setCharacterSize(52);
	logo.setPosition(-120, -140);
	logo.setString("Bubble.io");

	window.setView(view);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			window.clear();
			start.setFillColor(sf::Color::White);
			if (sf::IntRect(500, 500, 1000, 200).contains(sf::Mouse::getPosition(window))) {
				start.setFillColor(sf::Color::Magenta);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Text loading;
				loading.setFillColor(sf::Color::White);
				loading.setOutlineColor(sf::Color::Black);
				loading.setOutlineThickness(1);
				loading.setFont(font);
				loading.setCharacterSize(52);
				loading.setPosition(-100, 60);
				loading.setString("loading...");

				window.draw(rectangle);
				window.draw(start);
				window.draw(logo);
				window.draw(loading);
				window.display();
				return;
			}

			window.draw(rectangle);
			window.draw(logo);
			window.draw(start);
			window.display();
		}
	}
}