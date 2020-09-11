#pragma once
#include "Entity.h"
class Item : public Entity
{
public:
	Item(string name, string description, bool storage, bool canBeTaken);
	~Item();

	void showDescription();

public:
	bool storage;
	bool canBeTaken;
};

