#pragma once
#include "Entity.h"
#include "Exit.h"

class Room : public Entity
{
public:
	Room(string name, string description);
	~Room();

	void showDescription();

	Exit* getExit(const string& dir) const;
};

