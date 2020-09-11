#include "Creature.h"

Creature::Creature(string name, string description) 
	: Entity(name, description)
{
	type = creature;
}

Creature::~Creature()
{
}

void Creature::showDescription()
{
	cout << name << ": " << description << endl;
}

Room* Creature::getRoom() const
{
	return (Room*)location;
}
