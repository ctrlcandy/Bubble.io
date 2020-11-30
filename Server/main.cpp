/*!	\file main.cpp
*   \brief File includes main() and call of server
*/

#include "Server.h"

int main() {
	Server server;
	while (true) {
		server.receive();
	}

	system("pause");
}