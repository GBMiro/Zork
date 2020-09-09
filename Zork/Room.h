#pragma once
#include "Entity.h"

class Room : public Entity
{
public:
	Room(string name, string description);
	~Room();

	void showDescription();
};

