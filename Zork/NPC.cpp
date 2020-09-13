#include "NPC.h"
#include "Player.h"
#include "Room.h"
#include "utils.h"

NPC::NPC(const string& name, const string& description, int HP, int damage, int defense, const string& dialog, bool interactive, const string& answer)
	: Creature (name, description, HP, damage, defense)
{
	type = npc;
	this->dialog = dialog;
	this->interactive = interactive;
	riddleAnswer = answer;
}

NPC::~NPC()
{
}

void NPC::talkToPlayer() const
{
	cout << dialog << endl;
}

void NPC::checkAnswer(string answer)
{
	if (compare(riddleAnswer, answer)) {
		list<Entity*> exits;
		getRoom()->getEntityElementsByType(exits, wayOut);
		for (list<Entity*>::iterator it = exits.begin(); it != exits.end(); ++it) {
			if ((*it)->type == wayOut && ((Exit*)(*it))->isLocked) {
				((Exit*)(*it))->isLocked = false;
				cout << "All remaining blocked paths are now available" << endl;
				interactive = false;
			}
		}
	}
	else {
		attackPlayer();
	}
}

void NPC::attackPlayer() const
{
	Player* playerFound = (Player*) getRoom()->getPlayer();

	if (playerFound != NULL) {
		int damageDealt = damage - playerFound->defense > 0 ? damage - playerFound->defense : 0; // NPC ignores armor on player. It is intended
		playerFound->currentHP = playerFound->currentHP - damageDealt < 0 ? 0 : playerFound->currentHP - damageDealt;
		cout << name << " is draining your life force. You lost " << damageDealt << " health points." << endl;
		if (!playerFound->isAlive()) {
			cout << "You were killed by the " << name << ". Game Over" << endl;
		}
	}
	else {
		cout << "No player to attack" << endl;
	}
}

void NPC::update()
{
}
