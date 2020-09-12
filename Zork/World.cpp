#include <iostream>
#include "World.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "Item.h"
#include "NPC.h"

World::World()
{

	createWorld();

}

World::~World()
{
}

bool compareWorld(const string& first, const string& second) {
	return _stricmp(first.c_str(), second.c_str()) == 0;
}

void World::createWorld()
{
	//Create Rooms
	Room* room1 = new Room("Room 1", "This is the first room of the game");
	Room* room2 = new Room("Room 2", "Bottom left room");
	Room* room3 = new Room("Room 3", "Bottom right room");
	Room* room4 = new Room("Room 4", "Upper left room");
	Room* room5 = new Room("Room 5", "Upper right room");
	Room* finalRoom = new Room("Final Room", "This is the final room. Accessible from room 1");

	//Create Items
	Item* dagga = new Item("Dagga", "A small dagga. Sometimes less is more", false, true, true, weapon, 10);
	Item* key = new Item("Key", "Old key. Maybe it will take you to your doom", false, true, false, other, 0);
	Item* note = new Item("Note", "It says \"I can no longer fight that beast...\"", false, true, false, other, 0);
	Item* box = new Item("Box", "To store some items", true, true, false, other, 0);
	Item* table = new Item("Table", "An old table. It would be perfect to start a bonfire...", false, false, false, other, 0);
	Item* sword = new Item("Sword", "A long sword. You can feel a great power stored in it", false, true, true, weapon, 50);
	Item* healthPotion = new Item("Potion", "Contains an invisible liquid. No one knows what happens after drinking it...", false, true, false, potion, 100);

	dagga->changeLocation(room4);
	key->changeLocation(room5);
	note->changeLocation(box);
	box->changeLocation(room1);
	table->changeLocation(room1);
	healthPotion->changeLocation(room3);

	//Create Creatures
	Creature* troll = new Creature("Troll", "A cavern troll", 100, 20, 20);
	Creature* dragon = new Creature("Dragon", "From another world. It's your last trial. Beat it, and you will be long remembered.", 200, 50, 0);

	troll->changeLocation(room5);
	sword->changeLocation(troll);

	dragon->changeLocation(finalRoom);

	//Create NPC
	string dialog = 
		"This is your wisdom trial. "
		"Answer my riddle and the way will open. But be aware though only 3 guesses you will have...\n"
		"\"I am the beginning of everything, the end of everywhere.\n I am the beginning of eternity, the end of time and space...\n"
		" What am I?\"\n"
		"I'll be waiting your answer...";

	NPC* sphinx = new NPC("Sphinx", "A lost sphinx. It likes riddles", 100, 40, 100, dialog, true, "e");
	sphinx->changeLocation(room2);

	//Create Connections
	Exit* from1to2 = new Exit("Room1to2", "Passage from room 1 to room 2", room1, room2, west, false, NULL);
	Exit* from2to1 = new Exit("Room2to1", "Passage from room 2 to room 1", room2, room1, east, false, NULL);

	from1to2->changeLocation(room1);
	from2to1->changeLocation(room2);

	Exit* from1to3 = new Exit("Room1to3", "Passage from room 1 to room 3", room1, room3, east, false, NULL);
	Exit* from3to1 = new Exit("Room3to1", "A Passage from room 3 to room 1", room3, room1, west, false, NULL);

	from1to3->changeLocation(room1);
	from3to1->changeLocation(room3);

	Exit* from2to4 = new Exit("Room2to4", "Passage from room 2 to room 4", room2, room4, north, true, NULL);
	Exit* from4to2 = new Exit("Room4to2", "Passage from room 4 to room 2", room4, room2, south, false, NULL);

	from2to4->changeLocation(room2);
	from4to2->changeLocation(room4);

	Exit* from3to5 = new Exit("Room3to5", "Passage from room 3 to room 5", room3, room5, north, false, NULL);
	Exit* from5to3 = new Exit("Room5to3", "Passage from room 5 to room 3", room5, room3, south, false, NULL);

	from3to5->changeLocation(room3);
	from5to3->changeLocation(room5);

	Exit* from1toFinal = new Exit("Room1toFinal", "You can see a dark passage behind the door", room1, finalRoom, north, true, key);
	Exit* fromFinalto1 = new Exit("FinalRoomto1", "A dark passage back to the entrance", finalRoom, room1, south, false, key);

	from1toFinal->changeLocation(room1);
	fromFinalto1->changeLocation(finalRoom);

	//Create player
	newPlayer = new Player("Link", "Our hero for this adventure", 100, 40, 0);

	newPlayer->changeLocation(room1);

	this->worldElements.push_back(newPlayer);

	this->worldElements.push_back(room1);
	this->worldElements.push_back(room2);
	this->worldElements.push_back(room3);
	this->worldElements.push_back(room4);
	this->worldElements.push_back(room5);
	this->worldElements.push_back(finalRoom);

	this->worldElements.push_back(from1to2);
	this->worldElements.push_back(from2to1);
	this->worldElements.push_back(from1to3);
	this->worldElements.push_back(from3to1);
	this->worldElements.push_back(from2to4);
	this->worldElements.push_back(from4to2);
	this->worldElements.push_back(from3to5);
	this->worldElements.push_back(from5to3);
	this->worldElements.push_back(from1toFinal);
	this->worldElements.push_back(fromFinalto1);

	this->worldElements.push_back(dagga);
	this->worldElements.push_back(note);
	this->worldElements.push_back(key);
	this->worldElements.push_back(box);
	this->worldElements.push_back(table);
	this->worldElements.push_back(sword);
	this->worldElements.push_back(healthPotion);

	this->worldElements.push_back(troll);
	this->worldElements.push_back(dragon);

	this->worldElements.push_back(sphinx);
}

void World::showRoomsDescriptions() {
	for (vector<Entity*>::iterator iter = worldElements.begin(); iter != worldElements.end(); ++iter) {
		if ((*iter)->type == room) {
			((Room *)*iter)->showDescription();
		}
	}
}

void World::showWorldElements() {
	for (vector<Entity*>::iterator iter = worldElements.begin(); iter != worldElements.end(); ++iter) {
		if ((*iter)->type == room) {
			((Room *)*iter)->showDescription();
		}
		else if ((*iter)->type == wayOut) {
			((Exit *)*iter)->showDescription();
		}
	}
}

bool World::executeCommand(vector<string>& command) {
	bool found = true;

	switch (command.size()) {
		case 1: {
			if (compareWorld(command[0], "look")) {
				newPlayer->showDescription(command);
			}
			else if (compareWorld(command[0], "north")) {
				newPlayer->go(command);
			}
			else if (compareWorld(command[0], "south")) {
				newPlayer->go(command);
			}
			else if (compareWorld(command[0], "east")) {
				newPlayer->go(command);
			}
			else if (compareWorld(command[0], "west")) {
				newPlayer->go(command);
			}
			else if (compareWorld(command[0], "inventory")) {
				newPlayer->showInventory();
			}
			else if (compareWorld(command[0], "stats")) {
				newPlayer->showStats(command);
			}
			else {
				found = false;
			}
			break;
		}
		case 2: {
			if (compareWorld(command[0], "look")) {
				newPlayer->showDescription(command);
			}
			else if (compareWorld(command[0], "take")) {
				newPlayer->take(command);
			}
			else if (compareWorld(command[0], "drop")) {
				newPlayer->drop(command);
			}
			else if (compareWorld(command[0], "stats")) {
				newPlayer->showStats(command);
			}
			else if (compareWorld(command[0], "attack")) {
				newPlayer->attack(command);
			}
			else if (compareWorld(command[0], "equip")) {
				newPlayer->equip(command);
			}
			else if (compareWorld(command[0], "unequip")) {
				newPlayer->unEquip(command);
			}
			else if (compareWorld(command[0], "loot")) {
				newPlayer->loot(command);
			}
			else if (compareWorld(command[0], "drink")) {
				newPlayer->drink(command);
			}
			else {
				found = false;
			}
			break;
		}
		case 3: {
			if (compareWorld(command[0], "talk")) {
				newPlayer->talkNPC(command);
			}
			else {
				found = false;
			}
			break;
		}
		case 4: {
			if (compareWorld(command[0], "open")) {
				newPlayer->open(command);
			}
			else if (compareWorld(command[0], "close")) {
				newPlayer->close(command);
			}
			else if (compareWorld(command[0], "take")) {
				newPlayer->take(command);
			}
			else if (compareWorld(command[0], "drop")) {
				newPlayer->drop(command);
			}
			else if (compareWorld(command[0], "answer")) {
				newPlayer->answerNPC(command);
			}
			break;
		}
		default:
			found = false;
	}
	return found;
}

bool World::worldTurn()
{
	for (vector<Entity*>::iterator it = worldElements.begin(); it != worldElements.end(); ++it) {
		(*it)->update();
	}
	return newPlayer->isAlive();
}


