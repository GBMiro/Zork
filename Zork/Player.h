#pragma once
#include "Creature.h"
#include <vector>

class Player : public Creature
{
public:
	Player(string name,string description);
	~Player();

	void showDescription(const vector<string>& obj);
	void go(const vector<string>& dir);
	void take(const vector<string>& object);
	void drop(const vector<string>& object);
	virtual void showInventory();
};


