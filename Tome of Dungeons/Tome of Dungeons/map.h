#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

using namespace std;

class map
{
public:
	map();
	// Referemce parametre, also referencing the enemies vector, since if not it would modify or copy all the elements
	void load(string mapName, Player &player);
	string padding(int count, char character);
	void header(Player player, string enemyName = "", int playerDamage = 0, int enemyDamage = 0, bool playerDead = false, bool enemyDead = false);
	void print();

	// Function responsible for player movement
	void playerMove(char input, Player &player);
	// Function responsible for monster movement, targeting the player as reference
	void enemyMove(Player &player);

	// Getters
	// This will return the actual grid and its content
	char getGrid(int x, int y);
	// Setters
	void setGrid(int x, int y, char grid);

private:
	void processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY);
	void proccesMovePlayer(Player &player, int targetX, int targetY);
	// Battle the monster at this grid position
	void battleCase(Player &player, int targetX, int targetY);
	vector <Enemy> _enemies;
	vector <string> _mapData;

};

//Contains the data for the level, allow the player, the monster, npcs to move around and interac
// when a level created first, it has no data


// _ used for local variables
// like    _enemy