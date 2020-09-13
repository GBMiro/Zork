#include "Player.h"
#include "Exit.h"
#include "Item.h"
#include "NPC.h"
#include "utils.h"
#include <iostream>

Player::Player(const string& name, const string& description, int HP, int damage, int defense)
	: Creature(name, description, HP, damage, defense)
{
	type = player;
	victory = false;
}

Player::~Player()
{
}

void Player::showDescription(const vector<string>& action) const
{
	if (isAlive()) {
		if (action.size() == 1) {
			location->showDescription();
		}
		else if (action.size() == 2) {
			list<Entity*> elements;
			string lookAt = action[1];
			getRoom()->getEntityElements(elements);
			for (list<Entity*>::const_iterator it = elements.begin(); it != elements.end(); ++it) {
				if (compare((*it)->name, lookAt) || ((*it)->type == wayOut && compare(((Exit*)(*it))->types[((Exit*)(*it))->direction], lookAt))) {
					(*it)->showDescription();
					return;
				}
			}
			cout << "You don't see a thing" << endl;
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::go(const vector<string>& action)
{
	if (isAlive()) {
		string dir = action[0];
		Exit* exit = getRoom()->getExit(dir); // ((Room*)location)->getExit(dir[0]);

		if (exit == NULL) {
			cout << "You can't go to " << dir << endl;
		}
		else {
			if (exit->isLocked) {
				cout << "The path to that exit is blocked. Maybe you need to use something..." << endl;
			}
			else {
				cout << "You move " << dir << " to " << ((Room*)exit->destination)->name << endl;
				changeLocation((Room*)exit->destination);
				location->showDescription();
			}
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::take(const vector<string>& action)
{
	if (isAlive()) {
		string itemName = action[1];

		//We need to check if we are taking an item from another one or just taking one from the room
		if (action.size() == 2) {
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
			if (action.size() == 4) {
				string storageName = action[3];
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
						cout << itemName << " is not in here (" << storageName << ")" << endl;
					}
				}
				else {
					cout << "You don't see the item (" << storageName << ") in your inventory nor in the room" << endl;
				}
			}
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::drop(const vector<string>& action) 
{
	if (isAlive()) {
		string itemName = action[1];
		Item* itemFound = (Item*)getEntity(itemName, item);

		//We need to check if we are putting an item in another one or just dropping one.
		if (action.size() == 2) {
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
			if (action.size() == 4) {
				string storageName = action[3];
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
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::unLock(const vector<string>& action)
{
	if (isAlive()) {
		string dir = action[1];
		string itemUsed = action[3];

		Exit* exit = getRoom()->getExit(dir);
		Item* itemFound = (Item*)getEntity(itemUsed, item);

		if (exit == NULL) {
			cout << "You can't go to " << dir << endl;
		}
		else {
			if (itemFound == NULL) {
				cout << "You don't have the item: " << itemUsed << endl;
			}
			else {
				if (exit->key == itemFound) {
					cout << "You used " << itemUsed << " to open the door to the " << dir << endl;
					exit->isLocked = false;
				}
				else {
					cout << "This item can't be used to open the door to the " << dir << endl;
				}
			}
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::lock(const vector<string>& action)
{
	if (isAlive()) {
		string dir = action[1];
		string itemUsed = action[3];

		Exit* exit = getRoom()->getExit(dir);
		Item* itemFound = (Item*)getEntity(itemUsed, item);

		if (exit == NULL) {
			cout << "Nothing to close in that direction (" << dir << ")" << endl;
		}
		else {
			if (itemFound == NULL) {
				cout << "You don't have the proper item to unlock the door" << endl;
			}
			else {
				if (exit->key == itemFound) {
					cout << "You close the door leading to the " << dir << endl;
					exit->isLocked = true;
				}
				else {
					cout << "This item can't be used to close the door to the " << dir << endl;
				}
			}
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::attack(const vector<string>& action)
{
	if (isAlive()) {
		string creatureName = action[1];
		Creature* creatureFound = (Creature*)getRoom()->getEntity(creatureName, creature);

		if (creatureFound != NULL) {
			if (creatureFound->isAlive()) {
				int damageDealt = getTotalDamage() - creatureFound->defense > 0 ? getTotalDamage() - creatureFound->defense : 0;
				creatureFound->currentHP = creatureFound->currentHP - damageDealt < 0 ? 0 : creatureFound->currentHP - damageDealt;
				cout << "You attack the creature dealing " << damageDealt << " damage." << endl;
				if (!creatureFound->isAlive()) {
					cout << "You killed the " << creatureName << endl;
				}
			}
			else {
				cout << "The " << creatureName << " is dead." << endl;
			}
		}
		else {
			cout << "There is no creature " << creatureName << " here" << endl;
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::equip(const vector<string>& action)
{
	if (isAlive()) {
		string itemName = action[1];
		Item* itemFound = (Item*)getEntity(itemName, item);

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
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::unEquip(const vector<string>& action)
{
	if (isAlive()) {
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
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::loot(const vector<string>& action)
{
	if (isAlive()) {
		string creatureName = action[1];
		Creature* creatureFound = (Creature*)getRoom()->getEntity(creatureName, creature);

		if (creatureFound != NULL) {
			if (!creatureFound->isAlive()) {
				list<Entity* > creatureItems;
				creatureFound->getEntityElements(creatureItems);

				if (creatureItems.size() > 0) {
					for (list<Entity*>::iterator iter = creatureItems.begin(); iter != creatureItems.end(); ++iter) {
						Item* itemFound = (Item*)(*iter);
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
			cout << "There is no " << creatureName << " creature here" << endl;
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::drink(const vector<string>& action)
{
	if (isAlive()) {
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
	else {
		cout << "You are dead. Type quit to close the game." << endl;
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
	if (isAlive()) {
		string dragonName = "dragon";
		Creature* dragonFound = (Creature*)getRoom()->getEntity(dragonName, creature);

		if (dragonFound != NULL) {
			if (!dragonFound->isAlive() && !victory) {
				cout << "Congratulations, you have beaten the game! You set free your village from the tirany of the last dragon!" << endl;
				cout << "You can loot the dragon to see if it had something, revisit all rooms... To close the game, type quit." << endl;
				cout << "Thank you for playing!" << endl;
				victory = true;
			}
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::talkNPC(const vector<string>& action) const
{
	if (isAlive()) {
		string npcName = action[2];
		NPC* npcFound = (NPC*)getRoom()->getEntity(npcName, npc);

		if (npcFound != NULL) {
			npcFound->talkToPlayer();
		}
		else {
			cout << "There is no " << npcName << " npc here." << endl;
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::answerNPC(const vector<string>& action)
{
	if (isAlive()) {
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
			cout << "There is no " << npcName << " npc here." << endl;
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}



void Player::showInventory() const
{
	if (isAlive()) {
		list<Entity*> inventoryItems;
		getEntityElements(inventoryItems);

		if (inventoryItems.size() != 0) {
			cout << "-- Inventory --" << endl;
			for (list<Entity*>::const_iterator it = inventoryItems.begin(); it != inventoryItems.end(); ++it) {
				(*it)->showDescription();
			}
		}
		else {
			cout << "You have nothing in your bag" << endl;
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
	}
}

void Player::showStats(const vector<string>& action) const
{
	if (isAlive()) {
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
			Creature* creatureFound = (Creature*)getRoom()->getEntity(name, creature);
			NPC* npcFound = (NPC*)getRoom()->getEntity(name, npc);

			if (npcFound == NULL && creatureFound == NULL) {
				cout << "There is no " << name << " creature/npc here." << endl;
			}
			else if (npcFound == NULL) {
				creatureFound->showStats();
			}
			else {
				npcFound->showStats();
			}
		}
	}
	else {
		cout << "You are dead. Type quit to close the game." << endl;
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
