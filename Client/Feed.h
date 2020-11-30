#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Feed
{
	sf::RenderWindow* window; 
	std::vector<sf::CircleShape> circles;

public:
	Feed();
	Feed(sf::RenderWindow& window);

	sf::CircleShape& operator[](const size_t i);

	void setWindow(sf::RenderWindow& window);
	int size() const;
	void draw();
};

