/*!	\file Server.cpp
*   \brief File includes implementation of Server.h
*/

#include "Server.h"

bool isEqual(double x, double y) {
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

Server::Server() {
	socket.bind(SERVER_PORT);
	currentTime = time(NULL);

	std::string feedInfoStr;
	for (std::size_t i = 0; i < 150; ++i) {
		feedInfoStr += std::to_string(feed[i].getPosition().x) + "\n" + std::to_string(feed[i].getPosition().y) + "\n";
	}

	feedInfo << feedInfoStr;
}

void Server::send(sf::Packet& clientInfo) {
	std::string clientInfoStr;
	clientInfo >> clientInfoStr;

	std::string delimiter = "\n";

	int pos = clientInfoStr.find(delimiter);
	std::string clientIp = clientInfoStr.substr(0, pos);
	clientInfoStr.erase(0, pos + delimiter.length());

	pos = clientInfoStr.find(delimiter);
	unsigned short clientPort = atoi(clientInfoStr.substr(0, pos).c_str());
	clientInfoStr.erase(0, pos + delimiter.length());
	std::string buf;

	/// Somtimes information recive from port 0 (i don't know why), 
	/// but user can't use this port
	if (clientPort) {
		bool findAdress = false;

		for (std::size_t i = 0; i < adresses.size(); ++i) {
			if ((adresses[i].Ip == clientIp) && (adresses[i].port == clientPort)) {
				adresses[i].time = time(NULL);
				findAdress = true;

				// Player id (skip)
				pos = clientInfoStr.find(delimiter);
				buf += clientInfoStr.substr(0, pos);
				clientInfoStr.erase(0, pos + delimiter.length());

				// Radius
				pos = clientInfoStr.find(delimiter);
				adresses[i].bubble.setRadius(atoi(clientInfoStr.substr(0, pos).c_str()));
				buf += clientInfoStr.substr(0, pos);
				clientInfoStr.erase(0, pos + delimiter.length());

				// x coordinate
				pos = clientInfoStr.find(delimiter);
				float xc = atoi(clientInfoStr.substr(0, pos).c_str());
				buf += clientInfoStr.substr(0, pos);
				clientInfoStr.erase(0, pos + delimiter.length());

				// y coordinate
				pos = clientInfoStr.find(delimiter);
				float yc = atoi(clientInfoStr.substr(0, pos).c_str());
				buf += clientInfoStr.substr(0, pos);
				clientInfoStr.erase(0, pos + delimiter.length());

				adresses[i].bubble.setPosition(xc, yc);

				// score (skip)
				pos = clientInfoStr.find(delimiter);
				buf += clientInfoStr.substr(0, pos);
				clientInfoStr.erase(0, pos + delimiter.length());

				break;
			}
		}
		if (!findAdress) {
			std::cout << " New user: " << "IP " << clientIp << "; port " << clientPort << '\n';
			Adress newAdress;
			Bubble b;
			newAdress.Ip = clientIp;
			newAdress.port = clientPort;
			newAdress.bubble = b;
			newAdress.time = time(NULL);

			socket.send(feedInfo, newAdress.Ip, newAdress.port);
			adresses.push_back(newAdress);
		}
		else {
			std::string coordinates;
			srand(static_cast<unsigned int>(time(0)));
			std::size_t index;
			float x, y;
			while (pos != -1) {
				pos = clientInfoStr.find(delimiter);
				index = atoi(clientInfoStr.substr(0, pos).c_str());
				clientInfoStr.erase(0, pos + delimiter.length());

				pos = clientInfoStr.find(delimiter);
				x = atoi(clientInfoStr.substr(0, pos).c_str());
				clientInfoStr.erase(0, pos + delimiter.length());

				pos = clientInfoStr.find(delimiter);
				y = atoi(clientInfoStr.substr(0, pos).c_str());
				clientInfoStr.erase(0, pos + delimiter.length());

				//std::cout << index << " " << x << "  " << y << std::endl;
				feed[index].setPosition(rand() % 2950, rand() % 2950);
				coordinates += "\n" + std::to_string(index) +
					"\n" + std::to_string(feed[index].getPosition().x) +
					"\n" + std::to_string(feed[index].getPosition().y);
			}
			if (!coordinates.empty()) {
				clientInfoStr += clientIp + "\n" + std::to_string(clientPort) +
					"\n" + buf + coordinates;
				clientInfo << clientInfoStr;
			}
		}
	}

	double x, y, distance;
	float radius;
	sf::Packet deletePacket;
	std::string deletePacketStr = "Delete";
	for (std::size_t i = 0; i < adresses.size(); ++i) {
		for (std::size_t j = i + 1; j < adresses.size(); ++j) {
			radius = adresses[i].bubble.getRadius() + adresses[j].bubble.getRadius();
			x = std::pow(adresses[i].bubble.getPosition().x - adresses[j].bubble.getPosition().x, 2);
			y = std::pow(adresses[i].bubble.getPosition().y - adresses[j].bubble.getPosition().y, 2);
			distance = std::sqrt(x + y);
			if (isEqual(distance, radius) || distance <= radius) {
				if (adresses[i].bubble.getRadius() > adresses[j].bubble.getRadius()) {
					deletePacketStr += "\n" + adresses[j].Ip + "\n" + std::to_string(adresses[j].port);
				}
				else {
					deletePacketStr += "\n" + adresses[i].Ip + "\n" + std::to_string(adresses[i].port);
					adresses.erase(adresses.begin() + i);
				}
				deletePacket << deletePacketStr;

				for (std::size_t k = 0; k < adresses.size(); ++k) {
					socket.send(deletePacket, adresses[k].Ip, adresses[k].port);
				}
				adresses.erase(adresses.begin() + j);
				std::cout << adresses.size() << std::endl;
				deletePacketStr = "Delete";
			}
		}
	}

	std::size_t currTime = time(NULL);
	for (std::size_t i = 0; i < adresses.size(); ++i) {
		if ((currTime - adresses[i].time) > 2) {
			std::cout << " ...!! Delete: " << "IP " << adresses[i].Ip << " port " << adresses[i].port << '\n';
			std::cout << " ...!! Do not connect " << currTime - adresses[i].time << " seconds" << '\n';
			adresses.erase(adresses.begin() + i);
		}
	}

	for (std::size_t i = 0; i < adresses.size(); ++i) {
		socket.send(clientInfo, adresses[i].Ip, adresses[i].port);
	}

}

void Server::receive() {
	sf::Packet clientInfo;
	socket.receive(clientInfo, ANY_SENDER, ANY_PORT);
	send(clientInfo);
}