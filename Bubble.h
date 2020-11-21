#pragma once
#include <SFML/Graphics.hpp>

class Bubble
{
	sf::RenderWindow* window;
	sf::CircleShape circle;

	size_t player; 
	size_t score; 
	float speed;

public:
	Bubble(sf::RenderWindow& window, size_t player);

	float getRadius() const;
	void setRadius(const float radius);

	float getSpeed() const;
	void setSpeed(const float speed);

	const sf::Vector2f& getPosition() const;

	size_t getScore() const;
	void increaseScore(const size_t value);

	void draw();
	void update();
};

