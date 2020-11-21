#pragma once

#include <SFML/Graphics.hpp>
#include "Bubble.h"
#include "Feed.h"

class Bubbleio
{

public:
	Bubbleio() = delete;

	static void play();
	static void update(Bubble& bubble, Feed& feed);
};

