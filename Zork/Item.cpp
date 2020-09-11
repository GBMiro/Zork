#include "Item.h"

Item::Item(string name, string description, bool storage, bool canBeTaken)
	: Entity(name, description)
{
	type = item;
	this->storage = storage;
	this->canBeTaken = canBeTaken;
}

Item::~Item()
{
}

void Item::showDescription()
{
	cout << name << ": " << description << "." << endl;

	if (entityElements.size() != 0) {
		cout << "Contains the following: " << endl;
		for (list<Entity*>::iterator it = entityElements.begin(); it != entityElements.end(); ++it) {
			cout << "- " << (*it)->name << endl;
		}
	}
}
