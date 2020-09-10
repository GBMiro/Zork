#include "Player.h"
#include "Exit.h"
#include "Item.h"
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
	location->showDescription();
}

void Player::go(const vector<string>& dir)
{
	Exit* exit = getRoom()->getExit(dir[0]); // ((Room*)location)->getExit(dir[0]);

	if (exit == NULL) {
		cout << "You can't go to " << dir[0] << endl;
		return;
	}

	cout << "You move " << dir[0] << " to " << ((Room*)exit->destination)->name << endl;
	changeLocation((Room*)exit->destination);
	location->showDescription();
	return;
}

void Player::take(const vector<string>& object)
{
	string itemName = object[1];
	Item* itemFound = (Item*)location->getEntity(itemName, item);

	if (itemFound != NULL) {
		itemFound->changeLocation(this);
		cout << "You took " << itemName << endl;
	}
	else {
		cout << "There is no " << itemName << " in this room." << endl;
	}
}

void Player::drop(const vector<string>& object)
{
	string itemName = object[1];
	Item* itemFound = (Item*)getEntity(itemName, item);

	if (itemFound != NULL) {
		itemFound->changeLocation(location);
		cout << "You dropped the " << itemName << endl;
	}
	else {
		cout << "You don't have this item" << endl;
	}
}

void Player::showInventory()
{
	list<Entity*> inventoryItems;
	getEntityElements(inventoryItems);

	if (inventoryItems.size() != 0) {
		cout << "-- Inventory --" << endl;
		for (list<Entity*>::iterator it = inventoryItems.begin(); it != inventoryItems.end(); ++it) {
			cout << (*it)->name << ": " << (*it)->description << endl;
		}
	}
	else {
		cout << "You have nothing in your bag" << endl;
	}
}

