#include "NPC.h"

NPC::NPC(string name, string description, string dialog, bool interactive, string answer) 
	: Creature (name, description)
{
	type = npc;
	this->dialog = dialog;
	this->interactive = interactive;
	riddleAnswer = answer;
}

NPC::~NPC()
{
}

void NPC::showDescription()
{
	cout << name << ": " << description << endl;
}

void NPC::talkToPlayer()
{
	cout << dialog << endl;
}

void NPC::checkAnswer(string answer)
{
	if (_stricmp(riddleAnswer.c_str(), answer.c_str()) == 0) {
		list<Entity*> exits;
		getRoom()->getEntityElementsByType(exits, wayOut);
		for (list<Entity*>::iterator it = exits.begin(); it != exits.end(); ++it) {
			if ((*it)->type == wayOut && ((Exit*)(*it))->isLocked) {
				((Exit*)(*it))->isLocked = false;
				cout << "All remaining blocked paths are now available" << endl;
			}
		}
	} 
}
