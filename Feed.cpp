#include "Feed.h"

Feed::Feed(sf::RenderWindow& window) {
	circles.resize(150);
	srand(static_cast<unsigned int>(time(0)));
	this->window = &window;

	for (size_t i = 0; i < 150; ++i) {
		circles[i].setRadius(10);
		circles[i].setPosition(rand() % 2950, rand() % 2950);
		circles[i].setFillColor(sf::Color::Red);
	}
}

int Feed::size() const {
	return circles.size();
}

sf::CircleShape& Feed::operator[](const size_t i) {
	return circles[i];
}

void Feed::draw() {
	for (size_t i = 0; i < 150; ++i) {
		window->draw(circles[i]);
	}
}