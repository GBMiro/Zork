#pragma once
#include <list>
#include <string>
#include <iostream>
#include <vector>

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

	virtual void showDescription();
	virtual void update();
	void changeLocation(Entity* newLocation);
	Entity* getEntity(string name, EntityType type);
	Entity* getPlayer() const;
	void getEntityElements(list<Entity*>& elements);
	void getEntityElementsByType(list<Entity*>& elements, EntityType type);


public:
	EntityType type;
	string name;
	string description;
	Entity* location; //Where is the entity, if not a room
	list<Entity*> entityElements; //Objects inside an Entity like an object inside a room

};

