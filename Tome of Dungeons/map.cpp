#include "pch.h"
#include "map.h"
#include <fstream> // Gets input from a file
#include <iostream>
#include <cstdio>
#include "Player.h"


using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
											//GLOBAL VARIABLES//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string headerBar;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
											//LOAD MAP & SET UP//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
map::map() {

}

// This will populate a map with data from a file
void map::load(string mapName, Player &player) {

	// Loads the map
	ifstream file;

	file.open(mapName);
	if (file.fail()) {
		perror(mapName.c_str());
		system("PAUSE");
		exit(1);
	}

	// Read it line by line then put them in the string with the getLine function
	string line;

	// While this is sucessful it puts all the data in the _levelData vector, line by line
	// Each line will be an element
	while (getline(file, line)) {
		_mapData.push_back(line);
	}


	file.close();
	// Process the map
	// The i loop, loops through each row
	// The j loop, loops through each character of the i'th row
	char grid;
	for (int i = 0; i < _mapData.size(); i++) {
		for (int j = 0; j < _mapData[i].size(); j++) {
			grid = _mapData[i][j];
			// This gets the current gird point we are looking at

			switch (grid) {

				//Player//
			case '@':
				player.setPosition(j, i);
				break;

				//Snake//
			case 'S':
				// This creates an enemy instantly, without creating a new variable for the enemy, discarded after
				_enemies.push_back(Enemy("Snake", grid, 1, 3, 0, 1, 0, 1, 5));
				// Defines and sets the enemies position when we bump into it
				_enemies.back().setPosition(j, i);
				break;

				//Bandit//
			case 'B':
				_enemies.push_back(Enemy("Bandit", grid, 1, 10, 2, 3, 1, 4, 10));
				_enemies.back().setPosition(j, i);
				break;

				//Wolf//
			case 'W':
				_enemies.push_back(Enemy("Wolf", grid, 2, 12, 0, 5, 0, 3, 15));
				_enemies.back().setPosition(j, i);
				break;

				//Orc//
			case 'O':
				_enemies.push_back(Enemy("Orc", grid, 2, 15, 5, 4, 2, 5, 15));
				_enemies.back().setPosition(j, i);
				break;

				//Goblin//
			case 'G':
				_enemies.push_back(Enemy("Goblin", grid, 1, 7, 0, 2, 0, 4, 4));
				_enemies.back().setPosition(j, i);
				break;
			}

		}

	}
}


string map::padding(int count, char character) {
	string paddingString(count, character);
	return paddingString;
}


void map::header(Player player, string enemyName, int playerDamage, int enemyDamage, bool playerDead, bool enemyDead) {

	string playerAttack = "";
	string enemyAttack = "";
	string deathMessage = "";
	string statMessage = "";
	string healthMessage = "";
	string getMana = "";
	string getAttack = "";
	string getDefense = "";
	string getExperience = "";

	//make combat messages if there is an enemy
	if (enemyName != "") {
		playerAttack = " You have dealt " + to_string(playerDamage) + " damage to the " + enemyName + "!";
		enemyAttack = " The " + enemyName + " has dealt " + to_string(enemyDamage) + " damage to you!";
	}
	if (enemyDead) {
		deathMessage = " You defeated the " + enemyName;
	}
	else if (playerDead) {
		deathMessage = " The " + enemyName + " killed you!";
	}

	//build the header bar
	headerBar = padding(20, '#') + " - LOG - " + padding(20, '#') + padding(7, '#') + " - STATS - " + padding(7, '#') + padding(6, '#') + " - BAG - " + padding(6, '#') + "\n";
	headerBar += "#" + padding(47, ' ') + "#" + padding(25, ' ') + "#" + padding(19, ' ') + "#" + "\n";
	statMessage = " LVL " + to_string(player.getLevel()) + "    Exp  " + to_string(player.getExperience()); //stats information
	headerBar += "#" + playerAttack + padding(47 - playerAttack.length(), ' ') + "#" + statMessage + padding(25 - statMessage.length(), ' ') + "#" + padding(19, ' ') + "#" + "\n";
	statMessage = " HP  " + to_string(player.getHealth()) + "   MP  " + to_string(player.getMana()); //stats information
	headerBar += "#" + enemyAttack + padding(47 - enemyAttack.length(), ' ') + "#" + statMessage + padding(25 - statMessage.length(), ' ') + "#" + padding(18, ' ') + " #" + "\n";
	statMessage = " Atk " + to_string(player.getAttack()) + "   Def " + to_string(player.getDefense()); //stats information
	headerBar += "#" + deathMessage + padding(47 - deathMessage.length(), ' ') + "#" + statMessage + padding(25 - statMessage.length(), ' ') + "#" + padding(18, ' ') + " #" + "\n";
	headerBar += "#" + padding(47, ' ') + "#" + padding(25, ' ') + "#" + padding(19, ' ') + "#" + "\n";
}

// This function loops trough the mapData on by on. The "for" loop uses the rows as the base
// Goes on until the statement turns false by the " i " beign equal or bigger than mapData
void map::print() {

	cout << string(100, '\n');

	cout << headerBar;

	for (int i = 0; i < _mapData.size(); i++) {
		printf("%s\n", _mapData[i].c_str());
		//  %s print out a string and at the end it gets a new line, printf uses c.strings
		// _mapData[i] always refers to the actuall i row after iterration
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
												//PLAYER MOVE//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void map::playerMove(char input, Player &player) {

	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	switch (input) {

		// Move up
	case 'w':
	case 'W':
		// Player moves up on the Y coordinate, so -1 gets subed out
			// Where player is		where player moves
		proccesMovePlayer(player, playerX, playerY - 1);
		break;

		// Move left
	case 'a':
	case 'A':
		// Player moves left on the X coordinate, so -1 gets subed out
		proccesMovePlayer(player, playerX - 1, playerY);
		break;

		// Move down
	case 's':
	case 'S':
		// Player moves down on the Y coordinate, so +1 gets added
		proccesMovePlayer(player, playerX, playerY + 1);
		break;

		// Move right
	case 'd':
	case 'D':
		// player moves right on the X coordinate, so +1 gets added
		proccesMovePlayer(player, playerX + 1, playerY);
		break;

		// Not a valid key
	default:
		printf("Not a valid key!\n");
		system("PAUSE");
		break;

	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
												//ENEMY MOVE//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// It is a map function.
void map::enemyMove(Player &player) {

	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	player.getPosition(playerX, playerY);

	// Loops through each monster and update them.
	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);
		switch (aiMove) {
			// Move up
		case 'w':
			// Player moves up on the Y coordinate, so -1 gets subed out
				// Where player is		where player moves
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;

			// Move left
		case 'a':
			// Player moves left on the X coordinate, so -1 gets subed out
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;

			// Move down
		case 's':
			// Player moves down on the Y coordinate, so +1 gets added
			processEnemyMove(player, i, enemyX + 1, enemyY+1);
			break;

			// Move right
		case 'd':
			// player moves right on the X coordinate, so +1 gets added
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									//PROCESS PLAYER MOVE	GET & SET GRID//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char map::getGrid(int x, int y) {
	// Y comes first since, y is the row
	// Then x since its the collum
	return _mapData[y][x];
}

void map::setGrid(int x, int y, char grid) {
	_mapData[y][x] = grid;

}

void map::proccesMovePlayer(Player &player, int targetX, int targetY) {

	int playerX;
	int playerY;
	player.getPosition(playerX, playerY);

	char moveGrid = getGrid(targetX, targetY);

	switch (moveGrid) {
	case '-':
		// Opening a door
		setGrid(playerX, playerY, '@');
		setGrid(targetX, targetY, ' ');
		break;

	case ' ':
		// Player moves, the ' ' and '@' gets switched.
		// The players new positions gets set to the target position
		player.setPosition(targetX, targetY);
		setGrid(playerX, playerY, ' ');
		setGrid(targetX, targetY, '@');
		break;
	case '#':
		break;
		// Case needs to be added for npc, shop etc..

				// Anything that is not define otherwise is a monsterm which will result in a battle



	}
	battleCase(player, targetX, targetY);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									//PROCESS ENEMY MOVE     GET & SET GRID//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void map::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;


	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveGrid = getGrid(targetX, targetY);

	switch (moveGrid) {
	case ' ':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setGrid(enemyX, enemyY, ' ');
		setGrid(targetX, targetY, _enemies[enemyIndex].getGrid());
		break;
	case '#':
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										//ENEMY LOOK UP & BATTLE PROCESS//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defines the battle of the player and monster
// Decides which monster is battled
// This is donw by looping through the enemies


void map::battleCase(Player &player, int targetX, int targetY) {

	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int playerAttack;
	int enemyAttack;
	int combatResult;
	string enemyName = "";
	bool playerDied = false;
	bool enemyDied;
	bool combatHappened;


	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		//initialise variables
		combatHappened = false;
		enemyDied = false;
		playerAttack = 0;
		enemyAttack = 0;

		enemyName = _enemies[i].getEnemyName();
		_enemies[i].getPosition(enemyX, enemyY);

		if (targetX == enemyX && targetY == enemyY) {
			//Player Battle script here
			combatHappened = true;

			playerAttack = player.melee_attack();
			//	int playerMessage = printf("\nYou have dealt %d damage to the %s.\n", attackValue, enemyName.c_str());
				// The return value, which is the dmg received is stored in combatResult
			combatResult = _enemies[i].dmgReceive(playerAttack);

			if (combatResult != 0) {
				// If the enemy died, the grid is set to empty
				enemyDied = true;
				setGrid(targetX, targetY, '*');
				_enemies.erase(_enemies.begin() + i);

				player.playerExperience(combatResult);

			}

		}
		// Monster battle script
		//Check all for directions// Makes sure no other monster can attack
		if (playerX == enemyX - 1 && playerY == enemyY || playerX == enemyX + 1 && playerY == enemyY || playerY == enemyY - 1 && playerX == enemyX || playerY == enemyY + 1 && playerX == enemyX) {
			combatHappened = true;

			enemyAttack = _enemies[i].melee_attack();

			combatResult = player.dmgReceive(enemyAttack);

			if (combatResult != 0) {
				// If the player dies, the grid is set to =
				setGrid(playerX, playerY, 'x');
				playerDied = true;
			}

		}

		if (combatHappened) {
			header(player, enemyName, playerAttack, enemyAttack, playerDied, enemyDied);
			print();
		}
		if (playerDied) {
			exit(0);
		}

	}
}



// what is perror
// look up switch statment

//////////// ////////////////////Loot can be added after battle ///////////////////////////////////////////
