#include <iostream>
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Creature.h"

using namespace std;

Room::Room(string name, string description)
	: Entity(name, description)
{
	this->type = room;
}

Room::~Room()
{
}

void Room::showDescription()
{
	cout << "---   " << name << "   ---" << endl;
	cout << description << endl;

	//After room description, show all creatures, items and exits in the room

	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == creature) {
			((Creature *)*iter)->showDescription();
		}
	}

	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == wayOut) {
			((Item *)*iter)->showDescription();
		}
	}

	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == wayOut) {
			((Exit *) *iter)->showDescription();
		}
	}
}


