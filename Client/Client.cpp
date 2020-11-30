/*!	\file Client.cpp
*   \brief File includes implementation of Client.h
*/

#include "Client.h"

Client::Client() {
	socket.bind(sf::UdpSocket::AnyPort);
	User user;
	user.ip = sf::IpAddress::getLocalAddress().toString();
	user.port = socket.getLocalPort();

	users.push_back(user);
}

void Client::send(const Bubble& b, std::vector<std::pair<std::size_t, sf::Vector2f>>& newFeedPositions) {
	sf::Packet clientInfo;
	std::string clientInfoStr;
	users[0].bubble = b;

	clientInfoStr += users[0].ip + "\n";;
	clientInfoStr += std::to_string(users[0].port) + "\n";
	clientInfoStr += b.getPlayer() + "\n";
	clientInfoStr += std::to_string(b.getRadius()) + "\n";
	clientInfoStr += std::to_string(b.getPosition().x) + "\n";
	clientInfoStr += std::to_string(b.getPosition().y) + "\n";
	clientInfoStr += std::to_string(b.getScore());
	for (std::size_t i = 0; i < newFeedPositions.size(); ++i) {
		clientInfoStr += "\n" + std::to_string(newFeedPositions[i].first);
		clientInfoStr += "\n" + std::to_string(newFeedPositions[i].second.x);
		clientInfoStr += "\n" + std::to_string(newFeedPositions[i].second.y);
	}
	if (newFeedPositions.size()) {
		newFeedPositions.clear();
	}

	clientInfo << clientInfoStr;
	socket.send(clientInfo, SERVER_IP_ADDRESS, SERVER_PORT);
}

void Client::receive(Feed& f) {
	socket.receive(clientInfo, SERVER_IP_ADDRESS, SERVER_PORT);
	std::string clientInfoStr;
	clientInfo >> clientInfoStr;

	std::string delimiter = "\n";
	int pos = clientInfoStr.find(delimiter);

	if (!connected) {
		float x, y;
		for (std::size_t i = 0; i < f.size(); ++i) {
			pos = clientInfoStr.find(delimiter);
			x = atoi(clientInfoStr.substr(0, pos).c_str());
			clientInfoStr.erase(0, pos + delimiter.length());

			pos = clientInfoStr.find(delimiter);
			y = atoi(clientInfoStr.substr(0, pos).c_str());
			clientInfoStr.erase(0, pos + delimiter.length());

			f[i].setPosition(x, y);
		}
		connected = true;
	}
	else {
		std::string ip = clientInfoStr.substr(0, pos);

		if (ip == "Delete") {
			clientInfoStr.erase(0, pos + delimiter.length());

			pos = clientInfoStr.find(delimiter);
			ip = clientInfoStr.substr(0, pos);
			clientInfoStr.erase(0, pos + delimiter.length());

			pos = clientInfoStr.find(delimiter);
			unsigned int port = atoi(clientInfoStr.substr(0, pos).c_str());
			clientInfoStr.erase(0, pos + delimiter.length());

			if ((users[0].ip == ip) && (users[0].port == port)) {
				users.clear();
				SERVER_IP_ADDRESS = "";
				SERVER_PORT = 0;
				gameOver = true;

				return;
			}

			for (std::size_t i = 1; i < users.size(); ++i) {
				if ((users[i].ip == ip) && (users[i].port == port)) {
					users.erase(users.begin() + i);
					return;
				}
			}
		}

		clientInfoStr.erase(0, pos + delimiter.length());

		pos = clientInfoStr.find(delimiter);
		unsigned short port = atoi(clientInfoStr.substr(0, pos).c_str());
		clientInfoStr.erase(0, pos + delimiter.length());

		bool findUser = false;

		std::size_t index;
		for (size_t i = 0; i < users.size(); ++i) {
			if ((users[i].ip == ip) && (users[i].port == port)) {
				findUser = true;
				index = i;
				break;
			}
		}
		if (!findUser) {
			User newUser;
			newUser.ip = ip;
			newUser.port = port;

			index = users.size();
			users.push_back(newUser);
		}

		pos = clientInfoStr.find(delimiter);
		users[index].bubble.setPlayer(clientInfoStr.substr(0, pos));
		clientInfoStr.erase(0, pos + delimiter.length());

		pos = clientInfoStr.find(delimiter);
		users[index].bubble.setRadius(atoi(clientInfoStr.substr(0, pos).c_str()));
		clientInfoStr.erase(0, pos + delimiter.length());

		pos = clientInfoStr.find(delimiter);
		float x = atoi(clientInfoStr.substr(0, pos).c_str());
		clientInfoStr.erase(0, pos + delimiter.length());

		pos = clientInfoStr.find(delimiter);
		float y = atoi(clientInfoStr.substr(0, pos).c_str());
		clientInfoStr.erase(0, pos + delimiter.length());

		users[index].bubble.setPosition(x, y);

		pos = clientInfoStr.find(delimiter);
		users[index].bubble.setScore(atoi(clientInfoStr.substr(0, pos).c_str()));
		clientInfoStr.erase(0, pos + delimiter.length());

		/// Update feed
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

			f[index].setPosition(x, y);
		}
	}
}
