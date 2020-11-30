/*!	\file Feed.cpp
*   \brief File includes implementation of Feed.h
*/

#include "Feed.h"

Feed::Feed() {
	circles.resize(COUNT_OF_FEED);
	srand(static_cast<unsigned int>(time(0)));

	for (size_t i = 0; i < COUNT_OF_FEED; ++i) {
		circles[i].setPosition(rand() % 2950, rand() % 2950);
	}
}

std::size_t Feed::size() const {
	return circles.size();
}

sf::CircleShape& Feed::operator[](const std::size_t i) {
	return circles[i];
}
