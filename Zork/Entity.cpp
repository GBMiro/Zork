#include "Entity.h"
#include "utils.h"

using namespace std;

Entity::Entity(const string& name, const string& description)
{
	this->name = name;
	this->description = description;
}

Entity::~Entity()
{
}

void Entity::showDescription() const
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

Entity* Entity::getEntity(const string& name, EntityType type) const
{
	for (list<Entity*>::const_iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == type && compare((*iter)->name, name)) {
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

void Entity::getEntityElements(list<Entity*>& elements) const
{
	for (list<Entity*>::const_iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		elements.push_back(*iter);
	}
}

void Entity::getEntityElementsByType(list<Entity*>& elements, EntityType type) const
{
	for (list<Entity*>::const_iterator iter = entityElements.begin(); iter != entityElements.end(); ++iter) {
		if ((*iter)->type == type) {
			elements.push_back(*iter);
		}
	}
}
