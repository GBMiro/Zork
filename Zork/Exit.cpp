#include <iostream>
#include "Exit.h"

Exit::Exit(string name, string description, Room* source, Room* destination, DirectionType direction, bool isLocked, Item* key) 
	: Entity(name, description)
{
	this->source = source;
	this->destination = destination;
	this->direction = direction;
	this->isLocked = isLocked;
	this->key = key;
	this->type = wayOut;
}

Exit::~Exit()
{
}

void Exit::showDescription()
{
	cout << types[direction] << ": " << description << endl;
}
