#include "Bubbleio.h"
#include <string>
#include <cmath>
#include <limits>

void Bubbleio::play() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Bubble.io", sf::Style::None);

	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(965.f, 540.f));

	window.setFramerateLimit(60);

	sf::Event event;
	Bubble bubble(window, 1);
	Feed feed(window);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(3000, 3000));
	rectangle.setPosition(0, 0);
	rectangle.setFillColor(sf::Color::Yellow);

	sf::RectangleShape backgroundRectangle;
	backgroundRectangle.setSize(sf::Vector2f(6840, 5160));
	backgroundRectangle.setPosition(-1920, -1080);
	backgroundRectangle.setFillColor(sf::Color::White);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text scoreCount;
	scoreCount.setFillColor(sf::Color::Red);
	scoreCount.setFont(font);
	scoreCount.setCharacterSize(24);

	bool firstCheck = false;
	bool secondCheck = false;
	bool thirdCheck = false;

	size_t scoreCountX = 480;
	size_t scoreCountY = 270;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}

		window.clear();

		scoreCount.setString("Your score: " + std::to_string(bubble.getScore()));
		scoreCount.setPosition(bubble.getPosition().x - scoreCountX, bubble.getPosition().y - scoreCountY);
		window.draw(backgroundRectangle);
		window.draw(rectangle);
		view.setCenter(bubble.getPosition());

		if (!firstCheck && bubble.getRadius() > 120) {
			view.setSize(sf::Vector2f(1920.f, 1080.f));
			firstCheck = true;
			scoreCountX = 960;
			scoreCountY = 540;
			scoreCount.setCharacterSize(48);
		}
		else if (!secondCheck && bubble.getRadius() > 250) {
			view.setSize(sf::Vector2f(2880.f, 1620.f));
			secondCheck = true;
			scoreCountX = 1440;
			scoreCountY = 810;
			scoreCount.setCharacterSize(72);
		}
		else if (!thirdCheck && bubble.getRadius() > 400) {
			view.setSize(sf::Vector2f(3840.f, 2160.f));
			thirdCheck = true;
			scoreCountX = 1920;
			scoreCountY = 1080;
			scoreCount.setCharacterSize(96);
		}

		window.setView(view);
		window.draw(scoreCount);
		update(bubble, feed);
		window.display();
	}
}

bool isEqual(double x, double y) {
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

void Bubbleio::update(Bubble& bubble, Feed& feed) {
	feed.draw();
	bubble.draw();
	bubble.update();

	double x, y, distance;
	float radius = bubble.getRadius() + 10;

	for (size_t i = 0; i < feed.size(); ++i) {
		x = std::pow(bubble.getPosition().x - feed[i].getPosition().x, 2);
		y = std::pow(bubble.getPosition().y - feed[i].getPosition().y, 2);
		distance = std::sqrt(x + y);
		if (isEqual(distance, radius) || distance < radius)
		{
			feed[i].setPosition(rand() % 2950, rand() % 2950);
			bubble.increaseScore(1);
			bubble.setRadius(bubble.getRadius() + 0.3);
			bubble.setSpeed(bubble.getSpeed() - 0.01);
		}
	}
}