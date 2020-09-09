#pragma once
#include <list>
#include <string>

using namespace std;

enum EntityType {
	entity,
	creature,
	wayOut,
	room,
	item,
	npc,
	player
};

class Entity
{

public:
	Entity(string name, string description);
	~Entity();

public:
	EntityType type;
	string name;
	string description;
	Entity* location; //Where is the entity
	list<Entity*> entityElements; //Objects inside an Entity like an object inside a room

};

