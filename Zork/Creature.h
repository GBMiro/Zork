#pragma once
#include "Entity.h"
#include "Room.h"
class Creature : public Entity
{
public:
	Creature(string name, string description);
	~Creature();

	virtual void showDescription();
	Room* getRoom() const;

public:
	int hp; //Health points
};

