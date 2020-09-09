#pragma once
#include "Entity.h"

class Room;

class Exit : public Entity
{
	enum DirectionType
	{
		north,
		south,
		east,
		weast

	};

public:
	Exit();
	~Exit();

public:
	Room* source;
	Room* destination;
	DirectionType direction;
	bool isLocked;

};

