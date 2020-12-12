#Checking CMake version
cmake_minimum_required(VERSION 3.5)

#Project name and characteristics
project(Bubbleio VERSION 0.0.1 LANGUAGES CXX)

#Source .cpp list
set(SOURCES
	main.cpp
	Client.cpp
	Bubble.cpp
	Bubbleio.cpp
	Feed.cpp
	Menu.cpp
	Game.cpp
)

#Source .h list
set(HEADERS
	Client.h
	Bubble.h
	Bubbleio.h
	Feed.h
	Menu.h
	Game.h
)

#Creates executable named Bubbleio
add_executable(Bubbleio ${SOURCES} ${HEADERS})

#Specifying standard of C++ for Bubbleio project
set(CMAKE_CXX_STANDARD 11)

#Including SFML library
find_package(SFML 2.5 COMPONENTS graphics audio network REQUIRED)

target_link_libraries(Bubbleio sfml-graphics sfml-audio sfml-network)
