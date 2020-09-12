#pragma once
#include "Entity.h"

enum ItemType {
	weapon,
	armor,
	potion,
	other
};

class Item : public Entity
{
public:
	Item(string name, string description, bool storage, bool canBeTaken, bool canBeEquipped, ItemType itemType, int value);
	~Item();

	void showDescription();

public:
	bool storage; // if the item can contain other items
	bool canBeTaken;
	bool canBeEquipped;
	ItemType itemType;
	int value;
};

