/*!	\file Feed.cpp
*   \brief File includes implementation of Feed.h
*/

#include "Feed.h"

Feed::Feed() {
	circles.resize(150);

	for (sf::CircleShape c : circles) {
		c.setPosition(0, 0);
		c.setFillColor(sf::Color::Yellow);
		c.setRadius(10);
	}
}

Feed::Feed(sf::RenderWindow& window) : Feed() {
	this->window = &window;
}

sf::CircleShape& Feed::operator[](const std::size_t i) {
	return circles[i];
}

void Feed::setWindow(sf::RenderWindow& window) {
	this->window = &window;
}

int Feed::size() const {
	return circles.size();
}

void Feed::draw() {
	for (std::size_t i = 0; i < 150; ++i) {
		window->draw(circles[i]);
	}
}