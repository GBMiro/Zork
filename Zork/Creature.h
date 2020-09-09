#pragma once
#include "Entity.h"
class Creature : public Entity
{
public:
	Creature();
	~Creature();

public:
	int hp; //Health points
};

