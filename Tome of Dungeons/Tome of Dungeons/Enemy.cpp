#include "pch.h"
#include "Enemy.h"
#include <string>
#include <random>
#include <ctime>


Enemy::Enemy(string name, char grid, int level, int health, int mana, int melee_attack, int magic_attack, int defense, int experience) {
	_name = name;
	_grid = grid;
	_level = level;
	_health = health;
	_mana = mana;
	_melee_attack = melee_attack;
	_magic_attack = magic_attack;
	_defense = defense;
	_experience_value = experience;
}

int Enemy::melee_attack() {
	static default_random_engine rngEngine(time(NULL));
	uniform_int_distribution<int> attackValue(0, _melee_attack);

	return attackValue(rngEngine);
}

//Sets player position
void Enemy::setPosition(int x, int y) {
	_x = x;
	_y = y;
}
//Gets players position
void Enemy::getPosition(int &x, int &y) {
	x = _x;
	y = _y;
}

int Enemy::dmgReceive(int melee_attack) {
	melee_attack -= _defense;  //melee attack is affected by defense value, then the dmg is dealt
	//Check if the attack does dmg or not
	if (melee_attack > 0) {
		_health -= melee_attack;
		//check if enemy is dead or not
		if (_health <= 0) {
			// returns the exp value if the enemy is dead
			return _experience_value;
		}
	}
	return 0;
}

char Enemy::getMove(int playerX, int playerY) {

	static default_random_engine rngEngine(time(NULL));
	uniform_int_distribution<int> moveDirection(0, 6);

	// Distance calculation from player based on grid system
	// When distance calculated to avoid negative number results, the number's absolute was taken to ensure a positive number

	int distanceFromPlayer;
	int dx = _x - playerX;						// Distance of X
	int dy = _y - playerY;						// Distance of Y
	int adx = abs(dx);							// The absolute value of dx	
	int ady = abs(dy);							// The absolute value of dy

	distanceFromPlayer = adx + ady;

	// If distance less than 5 or equal then the enemy will move towards the player.
	if (distanceFromPlayer <= 5) {
		// Closer in the X direction , the enemy move on the X axis
		if (adx < ady) {
			if (dx > 0) {
				return 'a';
			}
			else {
				return 'd';
			}
		}
		// If the Y direction is closer, enemy move on the Y axis
		else {
			if (dy > 0) {
				return 'w';
			}
			else {
				return 's';
			}
		}
	}

	int randomMove = moveDirection(rngEngine);
	switch (randomMove) {

		// The move used by the enemy is based on the number which is generated randomly between 0 and 6
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return ' ';
	}

}