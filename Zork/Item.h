#pragma once
#include "Entity.h"
class Item : public Entity
{
public:
	Item();
	~Item();

	void showDescription();

public:
	bool take;
	bool container;
};

