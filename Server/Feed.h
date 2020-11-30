/*!	\file Feed.h
*   \brief File includes declaration of Feed functions without
	graphical elements for simple using in Server
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Feed
{
	std::size_t COUNT_OF_FEED = 150;

	std::vector<sf::CircleShape> circles;

public:
	Feed();

	std::size_t size() const;
	sf::CircleShape& operator[](const std::size_t i);

};

