#pragma once

#include <SFML/Graphics.hpp>

class Bubble
{
	sf::RenderWindow* window;
	sf::CircleShape circle;

	std::string player; 
	std::size_t score; 
	float speed;

public:
	Bubble();
	Bubble(const std::string& player);
	Bubble(sf::RenderWindow& window, const std::string& player);

	const Bubble& operator=(const Bubble& bubble);

	void setWindow(sf::RenderWindow& w);

	std::string getPlayer() const;
	void setPlayer(const std::string& player);

	float getRadius() const;
	void setRadius(const float radius);

	float getSpeed() const;
	void setSpeed(const float speed);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& coordinates);
	void setPosition(const float x, const float y);

	std::size_t getScore() const;
	void setScore(const std::size_t score);
	void increaseScore(const size_t value);

	void draw();
	void update();

};

