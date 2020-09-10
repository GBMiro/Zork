#include "Item.h"

Item::Item(string name, string description)
	: Entity(name, description)
{
	type = item;
}

Item::~Item()
{
}

void Item::showDescription()
{
	cout << name << ": " << description << endl;
}
