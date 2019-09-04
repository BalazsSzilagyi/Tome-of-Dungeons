#pragma once
#include "Player.h"
#include "map.h"
#include <iostream>
#include <string>

using namespace std;

class Engine
{
public:
	Engine(string mapName);

	void runGame();
	void movement();

private:
	Player _player;
	map _map;

};


// The Engine encapsulates all the necessary functionalities in its body and calls them.
//The rest of the program, can do their own separate work.
//Each part work separatelly, does not depend too much on other parts this way.
