#pragma once
#include <list>
#include <string>

using namespace std;
class Entity
{
	enum EntityType {
		entity,
		creature,
		exit,
		room,
		item,
		npc,
		player
	};

public:
	Entity();
	~Entity();

public:
	EntityType type;
	string name;
	string description;
	Entity* location; //Where is the entity
	list<Entity*> entityElements; //Objects inside an Entity like an object inside a room

};

