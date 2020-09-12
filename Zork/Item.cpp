#include "Item.h"

Item::Item(string name, string description, bool storage, bool canBeTaken, bool canBeEquipped, ItemType itemType, int value)
	: Entity(name, description)
{
	type = item;
	this->storage = storage;
	this->canBeTaken = canBeTaken;
	this->canBeEquipped = canBeEquipped;
	this->itemType = itemType;
	this->value = value;
}

Item::~Item()
{
}

void Item::showDescription()
{
	cout << name << ": " << description << ".";


	switch (itemType) {
		case weapon:
			cout << " Weapon with " << value << " attack points." << endl;
			break;
		case armor:
			cout << " Armor with " << value << " defense points." << endl;
			break;			
		default:
			cout << endl;
			break;
	}

	if (entityElements.size() != 0) {
		cout << "Contains the following: " << endl;
		for (list<Entity*>::iterator it = entityElements.begin(); it != entityElements.end(); ++it) {
			cout << "- " << (*it)->name << endl;
		}
	}
}
