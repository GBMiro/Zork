#pragma once
#include "Creature.h"
class NPC : public Creature
{
public:
	NPC(string name, string description, int HP, int damage, int defense, string dialog, bool interactive, string answer);
	~NPC();

	void talkToPlayer();
	void checkAnswer(string answer);
	void attackPlayer() const;
	void update();

public:
	string dialog;
	bool interactive;

private:
	string riddleAnswer;
};