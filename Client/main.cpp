/*!	\file main.cpp
*   \brief File includes main() and call of game's interface
*/

#include "Bubbleio.h"
#include "Client.h"

#include <iostream>

int main()
{
	Bubbleio::play();
	std::cout << "Game over!" << std::endl;

	system("pause");
}
