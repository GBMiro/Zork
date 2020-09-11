#pragma once
#include <vector>
#include "Entity.h"
#include "Item.h"

class Room;

enum DirectionType {
	north,
	south,
	east,
	west

};



class Exit : public Entity
{

public:
	Exit(string name, string description, Room* source, Room* destination, DirectionType direction, bool isLocked, Item* key);
	~Exit();

	void showDescription();

public:
	Room* source;
	Room* destination;
	DirectionType direction;
	Item* key;
	bool isLocked;
	vector<string> types = { "north", "south", "east", "west" };
};

