#pragma once
#include <random>
#include <ctime>

class Player
{
public:
	// Initialize the player class with init function, variables represent the player's properties
	Player();
	void init(int level, int health, int mana, int melee_attack, int magic_attack, int defense, int experience);

	// Player melee attack
	int melee_attack();

	// Player receives dmg
	int dmgReceive(int melee_attack);

	// Setters ==> sets player position
	void setPosition(int x, int y);

	// Adding exp to player after enemy kill
	void playerExperience(int experience);

	// Getters ==> gets players position
	void getPosition(int &x, int &y);

	int getLevel();
	int getHealth();
	int getMana();
	int getAttack();
	int getDefense();
	int getExperience();

private:
	// Properties, stored here

	// Maybe add name, which is taken from user at the start
	// Name will be sensitive to vulgar language
	int _level;
	int _health;
	int _mana;
	int _melee_attack;
	int _magic_attack;
	int _defense;
	int _experience;

	// Position, stored here
	int _x;
	int _y;
};


// Look up getPosition and setPosition
// Look up Classes
// What does it mean to initlaize and init funtion

