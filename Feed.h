#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <ctime> 
#include <vector>
#include <stdexcept>

class Feed
{
	sf::RenderWindow* window; 
	std::vector<sf::CircleShape> circles;

public:

	Feed(sf::RenderWindow& window);
	
	int size() const;
	sf::CircleShape& operator[](const size_t i);

	void draw();
};

