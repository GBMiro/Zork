#pragma once
#include "Entity.h"
class Creature : public Entity
{
public:
	Creature();
	~Creature();

	void showDescription();

public:
	int hp; //Health points
};

