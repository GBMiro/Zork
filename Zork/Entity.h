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
	Entity(const string& name, const string& description);
	~Entity();

	virtual void showDescription() const;
	virtual void update();

	void changeLocation(Entity* newLocation);
	void getEntityElements(list<Entity*>& elements) const;
	void getEntityElementsByType(list<Entity*>& elements, EntityType type) const;

	Entity* getEntity(const string& name, EntityType type) const;
	Entity* getPlayer() const;


public:
	EntityType type;
	string name;
	string description;
	Entity* location; //Where is the entity, if not a room
	list<Entity*> entityElements; //Objects inside an Entity like an object inside a room

};

