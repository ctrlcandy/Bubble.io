/*!	\file Bubble.cpp
*   \brief File includes implementation of Bubble.h
*/

#include "Bubble.h"

Bubble::Bubble() :
	player("Null"),
	score(0),
	speed(7) {
	circle.setRadius(20);
};

Bubble::Bubble(const std::size_t player) : Bubble() {
	this->player = player;
}

const Bubble& Bubble::operator=(const Bubble& bubble) {
	Bubble result;

	result.setPlayer(bubble.getPlayer());
	result.setScore(bubble.getScore());
	result.setSpeed(bubble.getSpeed());
	result.setPosition(bubble.getPosition());

	return result;
}

std::string Bubble::getPlayer() const {
	return player;
}

void Bubble::setPlayer(const std::string& player) {
	this->player = player;
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

size_t Bubble::getScore() const {
	return score;
}

void Bubble::setScore(const std::size_t score) {
	this->score = score;
}

void Bubble::increaseScore(const std::size_t value) {
	score += value;
}

