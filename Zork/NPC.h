#pragma once
#include "Creature.h"
class NPC : public Creature
{
public:
	NPC(const string& name, const string& description, int HP, int damage, int defense, const string& dialog, bool interactive, const string& answer);
	~NPC();

	void talkToPlayer() const;
	void checkAnswer(string answer);
	void attackPlayer() const;
	void update();

public:
	string dialog;
	bool interactive;

private:
	string riddleAnswer;
};