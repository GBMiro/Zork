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

	bool first = true;

	//After room description, show all creatures, items and exits in the room

	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == creature) {
			if (first) {
				cout << "There seems to be some creatures:" << endl;
				first = false;
			}
			((Creature *)*iter)->showDescription();
		}
	}

	first = true;

	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {	
		if ((*iter)->type == item) {
			if (first) {
				cout << "There seems to be some items:" << endl;
				first = false;
			}
			((Item *)*iter)->showDescription();
		}
	}

	first = true;

	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == wayOut) {
			if (first) {
				cout << "There seems to be some exits:" << endl;
				first = false;
			}
			((Exit *) *iter)->showDescription();
		}
	}
}

Exit* Room::getExit(const string& dir) const {
	for (list<Entity*>::const_iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == wayOut) {
			Exit* exit = (Exit*) *iter;
			if (exit->types[exit->direction] == dir) {
				return exit;
			}
		}
	}
	return NULL;
}


