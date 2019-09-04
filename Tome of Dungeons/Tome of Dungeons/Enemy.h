#pragma once
#include <string>

using namespace std;

class Enemy
{
public:
	Enemy(string name, char grid, int level, int health, int mana, int melee_attack, int magic_attack, int defense, int experience);

	// Enemy melee attack
	int melee_attack();



	// Setters ==> sets enemy position
	void setPosition(int x, int y);

	// Getters ==> gets enemy position
	void getPosition(int &x, int &y);
	string getEnemyName() { return _name; };
	// Enemy takes damage
	// If 0 returned, the enemy lives
	// If any other number returned, means enemy died, and the returned number is the exp given.
	int dmgReceive(int melee_attack);
	char getGrid() { return _grid; }

	// Getter AI move command
	// This makes the enemy moves towards the player's coordiantes
	char getMove(int playerX, int playerY);


private:
	string _name;
	char _grid;

	int _level;
	int _health;
	int _mana;
	int _melee_attack;
	int _magic_attack;
	int _defense;
	int _experience_value;

	// Grid position
	int _x;
	int _y;

};
////////////		vector <Loot> possibleLoots														///////////////////////////////////////////
////////////		floating point numbers for percentages											///////////////////////////////////////////
///////////			later adding a property to the enemy for range, when it will engage the player	///////////////////////////////////////////