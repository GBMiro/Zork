#pragma once
#include "Entity.h"
#include "Room.h"
class Creature : public Entity
{
public:
	Creature(const string& name, const string& description, int HP, int damage, int defense);
	~Creature();

	virtual void showDescription() const;
	virtual bool isAlive() const;
	virtual void attack(const vector<string>& action) const;
	virtual void showStats() const;
	virtual void update();
	void attackPlayer() const;
	Room* getRoom() const;

public:
	int HP; //Health points
	int currentHP;
	int damage; //base damage
	int defense; //base defense
};

