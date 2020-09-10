#pragma once
#include "Creature.h"
class NPC : public Creature
{
public:
	NPC(string name, string description);
	~NPC();
};