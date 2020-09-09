#pragma once
#include "Entity.h"
class Item : public Entity
{
public:
	Item();
	~Item();

public:
	bool take;
	bool container;
};

