#include "pch.h"
#include "Player.h"


using namespace std;

// Constructor, position initialized to zero.
Player::Player() {
	_x = 0;
	_y = 0;
}

// Initialize properties for player Class.
void Player::init(int level, int health, int mana, int melee_attack, int magic_attack, int defense, int experience) {
	_level = level;
	_health = health;
	_mana = mana;
	_melee_attack = melee_attack;
	_magic_attack = magic_attack;
	_defense = defense;
	_experience = experience;
}

// Using random number generator seeded with time.
// Since its static, it gets generated only once and will be used so on.
// The Uniform int distib is a template
int Player::melee_attack() {
	static default_random_engine rngEngine(time(NULL));
	uniform_int_distribution<int> attackValue(0, _melee_attack);
	return attackValue(rngEngine);
}


// Sets player position.
void Player::setPosition(int x, int y) {
	_x = x;
	_y = y;
}

// Player exp system
void Player::playerExperience(int experience) {
	_experience += experience;

	// If the player has more than 100 exp, it levels up
	// Then substract the 100 exp from the total exp value
	// Then the character's stats get strenghtened
	while (_experience > 30) {
		printf("Level up!\n");
		printf("Level +1, Health +5, Mana +3, Melee Attack +2 , Magic Attack +2, Defense +2.\n");
		_experience -= 30;
		_level++;
		_health += 5;
		_mana += 3;
		_melee_attack += 2;
		_magic_attack += 2;
		_defense += 2;
		system("PAUSE");
	}
}

// Gets players position.
void Player::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

int Player::dmgReceive(int melee_attack) {
	melee_attack -= _defense;  //melee attack is affected by defense value, then the dmg is dealt
	//Check if the attack does dmg or not
	if (melee_attack > 0) {
		_health -= melee_attack;
		//check if enemy is dead or not
		if (_health <= 0) {
			// returns 1 if he is dead
			return 1;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
									//RETURNS PLAYER VALUES FOR STATS//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Returns level value
int Player::getLevel() {
	return _level;
}

// Returns health value
int Player::getHealth() {
	return _health;
}

// Returns mana value
int Player::getMana() {
	return _mana;
}

// Returns melee attac value
int Player::getAttack() {
	return _melee_attack;
}

// Returns defense value
int Player::getDefense() {
	return _defense;
}

// Returns experience value
int Player::getExperience() {
	return _experience;
}
// What is a template