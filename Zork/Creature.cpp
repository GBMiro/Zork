#include "Creature.h"
#include "Player.h"

Creature::Creature(string name, string description, int HP, int damage, int defense) 
	: Entity(name, description)
{
	type = creature;
	this->HP = HP;
	this->currentHP = HP;
	this->damage = damage;
	this->defense = defense;
}

Creature::~Creature()
{
}

void Creature::showDescription()
{
	cout << name << ": " << description << endl;
}

bool Creature::isAlive() const
{
	return currentHP > 0;
}

void Creature::attack(const vector<string>& object) const
{
}

void Creature::showStats() const
{
	cout << "Name: " << name << endl;
	cout << "Total health points: " << HP << endl;
	cout << "Current health points: " << currentHP << endl;
	cout << "Damage: " << damage << endl;
	cout << "Defense: " << defense << endl;
	cout << "Status: " << (this->isAlive() ? "Alive" : "Dead") << endl;
}

void Creature::update()
{
	if (isAlive()) {
		attackPlayer();
	}
}

void Creature::attackPlayer() const
{
		Player* playerFound = (Player*)getRoom()->getPlayer();
		if (playerFound != NULL) {
			int damageDealt = damage - playerFound->defense > 0 ? damage - playerFound->defense : 0;
			playerFound->currentHP = playerFound->currentHP - damageDealt < 0 ? 0 : playerFound->currentHP - damageDealt;
			cout << this->name << " attack you! You lost " << damageDealt << " health points." << endl;
			if (!playerFound->isAlive()) {
				cout << "You were killed by the " << this->name << ". Game Over" << endl;
			}
		}
}

Room* Creature::getRoom() const
{
	return (Room*)location;
}
