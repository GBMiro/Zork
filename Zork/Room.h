#pragma once
#include "Entity.h"
#include "Exit.h"

class Room : public Entity
{
public:
	Room(const string& name, const string& description);
	~Room();

	void showDescription() const;

	Exit* getExit(const string& dir) const;
};

