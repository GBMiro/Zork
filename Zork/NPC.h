#pragma once
#include "Creature.h"
class NPC : public Creature
{
public:
	NPC(string name, string description, string dialog, bool interactive, string answer);
	~NPC();

	void showDescription();
	void talkToPlayer();
	void checkAnswer(string answer);

public:
	string dialog;
	bool interactive;
private:
	string riddleAnswer;
};