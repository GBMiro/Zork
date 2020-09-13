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
	Item(const string& name, const string& description, bool storage, bool canBeTaken, bool canBeEquipped, ItemType itemType, const int value);
	~Item();

	void showDescription() const;

public:
	bool storage; // if the item can contain other items
	bool canBeTaken;
	bool canBeEquipped;
	ItemType itemType;
	int value;
};

