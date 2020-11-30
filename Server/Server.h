/*!	\file Server.h
*   \brief File includes declaration of Server's functions
*/

#pragma once

#include <../include/SFML/Network/UdpSocket.hpp>
#include <../include/SFML/Network/Packet.hpp>
#include "Feed.h"
#include "Bubble.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <limits>

class Server
{
	unsigned short SERVER_PORT = 55002;

	sf::IpAddress ANY_SENDER = sf::IpAddress::Any;
	unsigned short ANY_PORT = 0;

	/*
	*	!!! HOW TO PARSE PACKETS FROM CLIENT !!!
	*	Includes in std::string format with '\n' separator:
	*	sf::IpAddress Ip
	*	unsigned short port
	*	Circle:
	*	- player id
	*	- radius
	*	- x coordinate
	*	- y coordinate
	*	- score
	*	- speed
	*	Feed (intersections):
	*	- Column of these paramrthres with '\n' separator:
	*   --- feed num, feed new coordinates
	*/

	struct Adress
	{
		std::string Ip;		/// can conversion to sf::IpAddress
		unsigned short port; 
		Bubble bubble;
		time_t time;
	};

	sf::UdpSocket socket;
	std::vector<Adress> adresses;
	std::size_t currentTime;

	/// Player information calculate in client
	/// Feed information send from server
	Feed feed;
	sf::Packet feedInfo;

public:
	Server();

	void send(sf::Packet& clientInfo);
	void receive();
		
};

