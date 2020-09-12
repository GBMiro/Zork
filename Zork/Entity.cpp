#include "Entity.h"

using namespace std;

Entity::Entity(string name, string description)
{
	this->name = name;
	this->description = description;
}

Entity::~Entity()
{
}

void Entity::showDescription()
{
}

void Entity::update()
{
}

void Entity::changeLocation(Entity * newLocation)
{
	if (location != NULL) {
		location->entityElements.remove(this);
	}

	location = newLocation;

	if (location != NULL) {
		location->entityElements.push_back(this);
	}
}

Entity* Entity::getEntity(string name, EntityType type)
{
	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == type && _stricmp((*iter)->name.c_str(), name.c_str()) == 0) {
			return *iter;
		}
	}
	return NULL;
}

Entity* Entity::getPlayer() const
{
	for (list<Entity*>::const_iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == player) {
			return *iter;
		}
	}
	return NULL;
}

void Entity::getEntityElements(list<Entity*>& elements)
{
	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		elements.push_back(*iter);
	}
}

void Entity::getEntityElementsByType(list<Entity*>& elements, EntityType type)
{
	for (list<Entity*>::iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == type) {
			elements.push_back(*iter);
		}
	}
}
