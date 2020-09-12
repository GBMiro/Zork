#include "Player.h"
#include "Exit.h"
#include "Item.h"
#include "NPC.h"
#include <iostream>

Player::Player(string name, string description, int HP, int damage, int defense)
	: Creature(name, description, HP, damage, defense)
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

void Player::drop(const vector<string>& object) 
{
	string itemName = object[1];
	Item* itemFound = (Item*)getEntity(itemName, item);
	
	//We need to check if we are putting an item in another one or just dropping one.
	if (object.size() == 2) {
		if (itemFound != NULL) {
			if (itemFound == weaponEquipped) {
				weaponEquipped = NULL;
			}
			else {
				if (itemFound == armorEquipped) {
					armorEquipped = NULL;
				}
			}
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

void Player::attack(const vector<string>& action)
{
	string creatureName = action[1];
	Creature* creatureFound = (Creature*)getRoom()->getEntity(creatureName, creature);

	if (creatureFound != NULL) {
		if (creatureFound->isAlive()) {
			int damageDealt = getTotalDamage() - creatureFound->defense > 0 ? getTotalDamage() - creatureFound->defense : 0;
			creatureFound->currentHP = creatureFound->currentHP - damageDealt < 0 ? 0 : creatureFound->currentHP - damageDealt;
			cout << "You attack the creature dealing " << damageDealt << " damage." << endl;
			if (!creatureFound->isAlive()) {
				cout << "You killed the creature." << endl;
			}
		}
		else {
			cout << "The creature is dead." << endl;
		}
	}
	else {
		cout << "There is no creature named " << creatureName << endl;
	}
}

void Player::equip(const vector<string>& action)
{
	string itemName = action[1];
	Item* itemFound = (Item*) getEntity(itemName, item);
	
	if (itemFound != NULL) {
		switch (itemFound->itemType) {
			case weapon:
				weaponEquipped = itemFound;
				cout << "You equipped " << weaponEquipped->name << endl;
				break;
			case armor:
				armorEquipped = itemFound;
				cout << "You equipped " << armorEquipped->name << endl;
				break;
			default:
				cout << "You can't equip this" << endl;
				break;
		}
	}
	else {
		cout << "To equip an item you must have it in your inventory" << endl;
	}
}

void Player::unEquip(const vector<string>& action)
{
	string itemName = action[1];
	Item* itemFound = (Item*)getEntity(itemName, item);

	if (itemFound != NULL) {
		switch (itemFound->itemType) {
			case weapon:
				if (itemFound != weaponEquipped) {
					cout << itemName << " is not equipped" << endl;
				}
				else {
					weaponEquipped = NULL;
					cout << "You remove " << itemName << endl;
				}
				break;
			case armor:
				if (itemFound != armorEquipped) {
					cout << itemName << " is not equipped" << endl;
				}
				else {
					armorEquipped = NULL;
					cout << "You remove " << itemName << endl;
				}
				break;
			default:
				cout << "This can't even be equipped." << endl;
				break;
		}
	}
	else {
		cout << "To remove a weapon or armor you must have it in your inventory" << endl;
	}
}

void Player::loot(const vector<string>& action)
{
	string creatureName = action[1];
	Creature* creatureFound = (Creature*)getRoom()->getEntity(creatureName, creature);

	if (creatureFound != NULL) {
		if (!creatureFound->isAlive()) {
			list<Entity* > creatureItems;
			creatureFound->getEntityElements(creatureItems);
			
			if (creatureItems.size() > 0) {
				for (list<Entity*>::iterator iter = creatureItems.begin(); iter != creatureItems.end(); ++iter) {
					Item* itemFound = (Item*) (*iter);
					itemFound->changeLocation(this);
					cout << "You took: " << itemFound->name << endl;
				}
			}
			else {
				cout << "Nothing found..." << endl;
			}
		}
		else {
			cout << "You can't loot a living creature" << endl;
		}
	}
	else {
		cout << "There is no one called " << creatureName << endl;
	}
}

void Player::drink(const vector<string>& action)
{
	string itemName = action[1];
	Item* itemFound = (Item*)getEntity(itemName, item);

	if (itemFound != NULL) {
		if (itemFound->itemType == potion) {
			if (itemFound->value > 0) {
				if (currentHP != HP) {
					int healthToRestore = HP - currentHP;
					int healthRestored = (itemFound->value - healthToRestore >= 0 ? healthToRestore : itemFound->value);

					currentHP += healthRestored;
					itemFound->value = itemFound->value - healthRestored;

					cout << "The potion restored " << healthRestored << " health points" << endl;

					if (itemFound->value == 0) {
						cout << "There's nothing left" << endl;
					}
					else {
						cout << "There is some potion left" << endl;
					}
				}
				else {
					cout << "Your health is full" << endl;
				}
			}
			else {
				cout << "It's empty." << endl;
			}
		}
		else {
			cout << "You can't drink this!" << endl;
		}
	}
	else {
		cout << "You don't have this item" << endl;
	}
}

int Player::getTotalDamage() const
{
	if (weaponEquipped != NULL) {
		return weaponEquipped->value + damage;
	}
	else {
		return damage;
	}
}

int Player::getTotalDefense() const
{
	if (armorEquipped != NULL) {
		return armorEquipped->value + defense;
	}
	else {
		return defense;
	}
}

void Player::update()
{
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

void Player::showStats(const vector<string>& action) const
{
	if (action.size() == 1) {
		cout << "Name: " << name << endl;
		cout << "Total health points: " << HP << endl;
		cout << "Current health points: " << currentHP << endl;
		cout << "Damage: " << getTotalDamage() << endl;
		cout << "Defense: " << getTotalDefense() << endl;
		cout << "Status: " << (this->isAlive() ? "Alive" : "Dead") << endl;
	}
	else {
		string name = action[1];
		Creature* creatureFound = (Creature*) getRoom()->getEntity(name, creature);
		NPC* npcFound = (NPC*)getRoom()->getEntity(name, npc);
		
		if (npcFound == NULL && creatureFound == NULL) {
			cout << "There is no creature called " << name << " here." << endl;
		}
		else if (npcFound == NULL) {
			creatureFound->showStats();
		}
		else {
			npcFound->showStats();
		}
	}
}

void Player::showHelp() const
{
	cout << "Available commands for the player:" << endl;
	cout << "look -> Show room information" << endl;
	cout << "look X -> Show information of X" << endl;
	cout << "take X -> Take an item from the room into your inventory" << endl;
	cout << "take X from Y -> Take item X from inside item Y" << endl;
	cout << "drop X -> Drop on the floor the item X from your inventory" << endl;
	cout << "drop X into Y -> Put item X inside item Y. Not all items can have another one inside" << endl;
	cout << "drink X -> Drink item X" << endl;
	cout << "north -> Go north if possible" << endl;
	cout << "south -> Go south if possible" << endl;
	cout << "east -> Go east if possible" << endl;
	cout << "west -> Go west if possible" << endl;
	cout << "talk to X -> Talk to NPC X" << endl;
	cout << "answer X with Y -> Answer NPC X with Y" << endl;
	cout << "open X with Y -> Open door blocking direction X (north, south, east, west) with Y" << endl;
	cout << "close X with Y -> Close door of X (north, south, east, west) with Y " << endl;
	cout << "equip X -> Equip item X " << endl;
	cout << "unequip X -> Unequip item X" << endl;
	cout << "attack X -> Attack creature X" << endl;
	cout << "loot X -> Loot creature X to get its items" << endl;
	cout << "inventory -> Show your inventory" << endl;
	cout << "stats -> Show your stats" << endl;
	cout << "stats X -> Show stats of X" << endl;
	cout << "help -> Show available commands" << endl;
}
