/*!	\file Bubbleio.cpp
*   \brief File includes implementation of Bubbleio.h
*/

#include "Bubbleio.h"

void Bubbleio::play() {
	Bubbleio bubbleio;
	bubbleio.drawGame();
}

void Bubbleio::drawGame() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bubble.io", sf::Style::None);
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f));

	window.setFramerateLimit(60);

	sf::Event event;
	std::string name = "No name";

	Bubble bubble(window, name);

	Feed feed(window);
	Client client;

	feed.setWindow(window);

	std::vector<std::pair<std::size_t, sf::Vector2f>> newFeedPositions;

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(3000, 3000));
	rectangle.setPosition(0, 0);
	rectangle.setFillColor(sf::Color::White);

	sf::Texture rectangleTexture;
	const sf::Texture* pRT = &rectangleTexture;
	rectangleTexture.loadFromFile("Textures/background.png");
	rectangle.setTexture(pRT, true);

	sf::RectangleShape backgroundRectangle;
	backgroundRectangle.setSize(sf::Vector2f(6840, 5160));
	backgroundRectangle.setPosition(-SCREEN_WIDTH, -SCREEN_HEIGHT);
	backgroundRectangle.setFillColor(sf::Color::White);

	sf::Texture backgroundRectangleTexture;
	const sf::Texture* pBRT = &backgroundRectangleTexture;
	backgroundRectangleTexture.loadFromFile("Textures/blurBackground.png");
	backgroundRectangle.setTexture(pBRT, true);

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	sf::Text scoreCount;
	scoreCount.setFillColor(sf::Color::White);
	scoreCount.setOutlineColor(sf::Color::Black);
	scoreCount.setOutlineThickness(1);
	scoreCount.setFont(font);
	scoreCount.setCharacterSize(24);

	for (size_t i = 0; i < feed.size(); ++i) {
		feed[i].setFillColor(sf::Color::Yellow);
		feed[i].setRadius(10);
	}

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

		client.send(bubble, newFeedPositions);

		std::thread th([&]() {
			client.receive(feed);
			});
		th.detach();

		window.clear();

		scoreCount.setString("Your score: " + std::to_string(bubble.getScore()));
		scoreCount.setPosition(bubble.getPosition().x - scorePositionX, bubble.getPosition().y - scoreCountY);
		window.draw(backgroundRectangle);
		window.draw(rectangle);

		view.setCenter(bubble.getPosition());
		setUserView(bubble, view, scoreCount);
		window.setView(view);
		window.draw(scoreCount);

		update(bubble, feed, newFeedPositions);

		for (std::size_t i = 1; i < client.users.size(); ++i) {
			client.users[i].bubble.setWindow(window);
			client.users[i].bubble.draw();
		}

		window.display();

		/// \todo Correctly show players' intersection
		if (client.gameOver) {
			end();
		}
	}
}



void Bubbleio::end() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bubble.io", sf::Style::None);
	sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f));

	window.setFramerateLimit(60);

	sf::Event event;

	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	sf::Text endText;
	endText.setFillColor(sf::Color::Red);
	endText.setFont(font);
	endText.setCharacterSize(72);
	endText.setString("Game over!");
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

		endText.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		window.display();
	}
}


void Bubbleio::setUserView(const Bubble& bubble, sf::View& view, sf::Text& scoreCount) {
	if (!firstScreenCheck && bubble.getRadius() > 120) {
		view.setSize(sf::Vector2f(1920.f, 1080.f));
		firstScreenCheck = true;
		scorePositionX = 960;
		scoreCountY = 540;
		scoreCount.setCharacterSize(48);
	}
	else if (!secondScreenCheck && bubble.getRadius() > 250) {
		view.setSize(sf::Vector2f(2880.f, 1620.f));
		secondScreenCheck = true;
		scorePositionX = 1440;
		scoreCountY = 810;
		scoreCount.setCharacterSize(72);
	}
	else if (!thirdScreenCheck && bubble.getRadius() > 400) {
		view.setSize(sf::Vector2f(3840.f, 2160.f));
		thirdScreenCheck = true;
		scorePositionX = 1920;
		scoreCountY = 1080;
		scoreCount.setCharacterSize(96);
	}
}

bool isEqual(double x, double y) {
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

void Bubbleio::update(Bubble& bubble, Feed& feed, std::vector<std::pair<std::size_t, sf::Vector2f>>& newFeedPositions) {
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
			newFeedPositions.push_back(std::make_pair(i, feed[i].getPosition()));
			bubble.increaseScore(1);
			bubble.setRadius(bubble.getRadius() + 0.3);
			bubble.setSpeed(bubble.getSpeed() - 0.01);
		}
	}
}