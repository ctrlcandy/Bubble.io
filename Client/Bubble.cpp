/*!	\file Bubble.cpp
*   \brief File includes implementation of Bubble.h
*/

#include "Bubble.h"

Bubble::Bubble() :
	player("Null"),
	score(0),
	speed(7),
	window(nullptr)
{
	circle.setRadius(20);
	circle.setOrigin(20, 20);
	circle.setPosition(rand() % 1990, rand() % 1990);
	circle.setFillColor(sf::Color::Magenta);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(1);
};

Bubble::Bubble(const std::string& player) : Bubble() {
	this->player = player;
}

Bubble::Bubble(sf::RenderWindow& window, const std::string& player) : Bubble(player) {
	this->window = &window;
}

void Bubble::setWindow(sf::RenderWindow& window) {
	this->window = &window;
}

void Bubble::draw() {
	window->draw(circle);
}

const Bubble& Bubble::operator=(const Bubble& bubble) {
	Bubble result;

	result.setPlayer(bubble.player);
	result.setPosition(bubble.getPosition());
	result.setRadius(bubble.getRadius());
	result.setScore(bubble.score);
	result.setSpeed(bubble.speed);

	return result;
}

std::string Bubble::getPlayer() const {
	return player;
}

void Bubble::setPlayer(const std::string& p) {
	player = p;
}

float Bubble::getSpeed() const {
	return speed;
}

void Bubble::setSpeed(const float speed) {
	if (speed > 1) {
		this->speed = speed;
	}
	else {
		this->speed = 1;
	}
}

float Bubble::getRadius() const {
	return circle.getRadius();
}

void Bubble::setRadius(const float radius) {
	circle.setOrigin(radius, radius);
	circle.setRadius(radius);
}

sf::Vector2f Bubble::getPosition() const {
	return circle.getPosition();
}

void Bubble::setPosition(const sf::Vector2f& coordinates) {
	circle.setPosition(coordinates);
}

void Bubble::setPosition(const float x, const float y) {
	circle.setPosition(x, y);
}

std::size_t Bubble::getScore() const {
	return score;
}

void Bubble::setScore(const std::size_t score) {
	this->score = score;
}

void Bubble::increaseScore(const std::size_t value) {
	score += value;
}

void Bubble::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (circle.getPosition().y > circle.getRadius() + speed) {
			circle.setPosition(circle.getPosition().x, circle.getPosition().y - speed);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (circle.getPosition().y < 3000 - circle.getRadius() - speed) {
			circle.setPosition(circle.getPosition().x, circle.getPosition().y + speed);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (circle.getPosition().x > circle.getRadius() + speed) {
			circle.setPosition(circle.getPosition().x - speed, circle.getPosition().y);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (circle.getPosition().x < 3000 - circle.getRadius() - speed) {
			circle.setPosition(circle.getPosition().x + speed, circle.getPosition().y);
		}
	}
}
