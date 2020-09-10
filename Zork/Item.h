#pragma once
#include "Entity.h"
class Item : public Entity
{
public:
	Item(string name, string description);
	~Item();

	void showDescription();

public:
	bool take;
	bool container;
};

