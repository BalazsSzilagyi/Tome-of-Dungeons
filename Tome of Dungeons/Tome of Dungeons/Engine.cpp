#include "pch.h"
#include "Engine.h"
#include <iostream>
#include <conio.h>

using namespace std;

//Constructor sets up the game
Engine::Engine(string mapName) {

	//Initialize the player and its attributes / properties
	_player.init(1, 30, 1, 10, 1, 3, 0);

	// load loads in the player's position on the map and the map as well
	_map.load(mapName, _player);
	_map.header(_player);
	_map.print();
	system("PAUSE");

}

void Engine::runGame() {

	//flag singal
	bool stopGame = false;

	while (stopGame != true) {
		_map.print();
		movement();
		_map.enemyMove(_player);
	}
}

void Engine::movement() {
	char input;
	//printf("Use the W,A,S,D keys to move.");
	input = _getch();
	_map.playerMove(input, _player);
}