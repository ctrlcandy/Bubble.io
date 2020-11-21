#include "Bubble.h"

Bubble::Bubble(sf::RenderWindow& window, size_t player) {
	score = 0;
	speed = 7;
	this->player = player;
	this->window = &window;

	circle.setRadius(20);
	circle.setPosition(rand() % 1990, rand() % 1990);
	circle.setOrigin(20, 20);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(1);
}

void Bubble::draw() {
	window->draw(circle);
}

float Bubble::getSpeed() const {
	return speed;
}

void Bubble::setSpeed(const float speed) {
	if (speed > 0) {
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

const sf::Vector2f& Bubble::getPosition() const {
	return circle.getPosition();
}

size_t Bubble::getScore() const {
	return score;
}

void Bubble::increaseScore(const size_t value) {
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
