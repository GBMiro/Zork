#include "Item.h"

Item::Item(const string& name, const string& description, bool storage, bool canBeTaken, bool canBeEquipped, ItemType itemType, const int value)
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

void Item::showDescription() const
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

	//Check if this item has items inside
	if (entityElements.size() != 0) {
		cout << "Contains the following: " << endl;
		for (list<Entity*>::const_iterator it = entityElements.begin(); it != entityElements.end(); ++it) {
			cout << "- " << (*it)->name << endl;
		}
	}
}
