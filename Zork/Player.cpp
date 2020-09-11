#include "Player.h"
#include "Exit.h"
#include "Item.h"
#include "NPC.h"
#include <iostream>

Player::Player(string name, string description)
	: Creature(name, description)
{
	type = player;
}

Player::~Player()
{
}

void Player::showDescription(const vector<string>& obj)
{
	if (obj.size() == 1) {
		location->showDescription();
	}
	else if (obj.size() == 2) {
		list<Entity*> elements;
		string lookAt = obj[1];
		getRoom()->getEntityElements(elements);
		for (list<Entity*>::iterator it = elements.begin(); it != elements.end(); ++it) {
			if (_stricmp((*it)->name.c_str(), lookAt.c_str()) == 0 || ((*it)->type  == wayOut && _stricmp((((Exit*)(*it))->types[((Exit*)(*it))->direction]).c_str(), lookAt.c_str()) == 0)) {
				(*it)->showDescription();
				return;
			}
		}
		cout << "You don't see a thing" << endl;
	}

}

void Player::go(const vector<string>& dir)
{
	Exit* exit = getRoom()->getExit(dir[0]); // ((Room*)location)->getExit(dir[0]);

	if (exit == NULL) {
		cout << "You can't go to " << dir[0] << endl;
	}
	else {
		if (exit->isLocked) {
			cout << "The path to that exit is blocked. Maybe you need to use something..." << endl;
		}
		else {
			cout << "You move " << dir[0] << " to " << ((Room*)exit->destination)->name << endl;
			changeLocation((Room*)exit->destination);
			location->showDescription();
		}
	}
}

void Player::take(const vector<string>& object)
{
	string itemName = object[1];
	//cout << object.size() << endl;
	//We need to check if we are taking an item from another one or just taking one from the room
	if (object.size() == 2) {
		Item* itemFound = (Item*)location->getEntity(itemName, item);
		if (itemFound != NULL) {
			if (itemFound->canBeTaken) {
				itemFound->changeLocation(this);
				cout << "You took " << itemName << endl;
			}
			else {
				cout << "This item is too heavy to carry it with you." << endl;
			}
		}
		else {
			cout << "There is no " << itemName << " in this room." << endl;
		}
	}
	else {
		if (object.size() == 4) {
			string storageName = object[3];
			Item* storageFound = (Item*)getEntity(storageName, item);

			//Maybe the storage is in the room, not in our inventory
			if (storageFound == NULL) {
				storageFound = (Item*)getRoom()->getEntity(storageName, item);
			}

			if (storageFound != NULL) {

				Item* itemFound = (Item*)storageFound->getEntity(itemName, item);

				if (itemFound != NULL) {
					itemFound->changeLocation(this);
					cout << "You took " << itemName << " from the " << storageName << endl;
				}
				else {
					cout <<  itemName << " is not in here (" << storageName << ")" << endl;
				}
			}
			else {
				cout << "You don't see the item (" << storageName << ") in your inventory nor in the room" << endl;
			}
		}
	}
}

void Player::drop(const vector<string>& object) //Afegir cas que estiguin l'objecte a l'habitació, o el tingui jo. Ara estic suposont que quan faig drop into i take from ho tinc tot jo
{
	string itemName = object[1];
	Item* itemFound = (Item*)getEntity(itemName, item);

	//cout << object.size() << endl;
	
	//We need to check if we are putting an item in another one or just dropping one
	if (object.size() == 2) {
		if (itemFound != NULL) {
			itemFound->changeLocation(location);
			cout << "You dropped the " << itemName << endl;
		}
		else {
			cout << "You don't have this item" << endl;
		}
	}
	else {
		if (object.size() == 4) {
			string storageName = object[3];
			Item* storageFound = (Item*)getEntity(storageName, item);

			//Maybe the storage is in the room, not in our inventory
			if (storageFound == NULL) {
				storageFound = (Item*)getRoom()->getEntity(storageName, item);
			}

			//Maybe the item is not in our inventory
			if (itemFound == NULL) {
				itemFound = (Item*)getRoom()->getEntity(itemName, item);
			}

			if (itemFound != NULL) {
				if (storageFound != NULL) {
					if (storageFound->storage) {
						itemFound->changeLocation(storageFound);
						cout << "You put the " << itemName << " in the " << storageName << endl;
					}
					else {
						cout << "You can't leave " << itemName << " in or on " << storageName << endl;
					}
				}
				else {
					cout << "You don't have this item (" << storageName << ") nor it is in this room." << endl;
				}
			}
			else {
				cout << "You don't have this item (" << itemName << ") nor it is in this room" << endl;
			}
		}
	}

}

void Player::open(const vector<string>& action)
{
	string dir = action[1];
	string itemUsed = action[3];

	Exit* exit = getRoom()->getExit(dir);
	Item* itemFound = (Item*)getEntity(itemUsed, item);

	if (exit == NULL) {
		cout << "You can't go to " << dir << endl;
	}
	else {
		if (itemFound == NULL) {
			cout << "You don't have the item: "<< itemUsed << endl;
		}
		else {
			if (exit->key == itemFound) {
				cout << "You used " << itemUsed << " to open the pass to the " << dir << endl;
				exit->isLocked = false;
			}
			else {
				cout << "This item can't be used to open the path to the " << dir << endl;
			}
		}
	}

}

void Player::close(const vector<string>& action)
{
	string dir = action[1];
	string itemUsed = action[3];

	Exit* exit = getRoom()->getExit(dir);
	Item* itemFound = (Item*) getEntity(itemUsed, item);

	if (exit == NULL) {
		cout << "Nothing to close in that direction (" << dir << ")" << endl;
	}
	else {
		if (itemFound == NULL) {
			cout << "You don't have the proper item to unlock the path" << endl;
		}
		else {
			if (exit->key == itemFound) {
				cout << "You close the path leading to the " << dir << endl;
				exit->isLocked = true;
			}
			else {
				cout << "This item can't be used to close the path to the " << dir << endl;
			}
		}
	}
}

void Player::talkNPC(const vector<string>& action)
{
	string npcName = action[2];
	NPC* npcFound = (NPC*)getRoom()->getEntity(npcName, npc);

	if (npcFound != NULL) {
		npcFound->talkToPlayer();
	}
	else {
		cout << "There is no NPC named " << npcName << "here." << endl;
	}
}

void Player::answerNPC(const vector<string>& action)
{
	string npcName = action[1];
	string answer = action[3];

	NPC* npcFound = (NPC*)getRoom()->getEntity(npcName, npc);

	if (npcFound != NULL) {
		if (npcFound->interactive) {
			npcFound->checkAnswer(answer);
		}
		else {
			cout << "It won't listen to you..." << endl;
		}
	}
	else {
		cout << "There is no NPC named " << npcName << " here." << endl;
	}
}



void Player::showInventory()
{
	list<Entity*> inventoryItems;
	getEntityElements(inventoryItems);

	if (inventoryItems.size() != 0) {
		cout << "-- Inventory --" << endl;
		for (list<Entity*>::iterator it = inventoryItems.begin(); it != inventoryItems.end(); ++it) {
			(*it)->showDescription();
		}
	}
	else {
		cout << "You have nothing in your bag" << endl;
	}
}

