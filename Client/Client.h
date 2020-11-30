#pragma once
#include <../include/SFML/Network/UdpSocket.hpp>
#include <../include/SFML/Network/Packet.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Feed.h"
#include "Bubble.h"

class Client
{

	sf::IpAddress SERVER_IP_ADDRESS = sf::IpAddress::LocalHost;
	unsigned short SERVER_PORT = 55002;

	/*
	*	!!! HOW TO SEND PACKETS TO SERVER !!!
	*	Use in std::string format '\n' separator
	*
	*	Packet field:
	*	sf::IpAddress Ip
	*	unsigned short port
	*	Circle:
	*	- player id
	*	- radius
	*	- x coordinate
	*	- y coordinate
	*	- score
	*	Feed (intersections):
	*	- Column of these paramrthres with ' ' separator:
	*   --- feed num, feed new coordinates
	*/
	sf::Packet clientInfo;

	sf::UdpSocket socket;

	struct User {
		Bubble bubble;

		std::string ip;
		unsigned short port;
	};
	bool connected = false;

public:
	bool gameOver = false;
	std::vector<User> users;

	Client();

	void send(const Bubble& b, std::vector<std::pair<std::size_t, sf::Vector2f>>& newFeedPositions);
	void receive(Feed& f);

};


