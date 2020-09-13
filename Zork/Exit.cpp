#include <iostream>
#include "Exit.h"

Exit::Exit(const string& name, const string& description, Room* source, Room* destination, DirectionType direction, bool isLocked, Item* key) 
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

void Exit::showDescription() const
{
	cout << "-" << types[direction] << ": " << description << endl;
}
