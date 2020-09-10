#include <iostream>
#include "World.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "Item.h"

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
	//Create Rooms, Exits and connections
	Room* room1 = new Room("Room 1", "This is the first room of the game");
	Room* room2 = new Room("Room 2", "Bottom left room");
	Room* room3 = new Room("Room 3", "Bottom right room");
	Room* room4 = new Room("Room 4", "Upper left room");
	Room* room5 = new Room("Room 5", "Upper right room");
	Room* finalRoom = new Room("Final Room", "This is the final room. Accessible from room 1");


	Exit* from1to2 = new Exit("Room1to2", "Passage from room 1 to room 2", room1, room2, west, false);
	Exit* from2to1 = new Exit("Room2to1", "Passage from room 2 to room 1", room2, room1, east, false);

	from1to2->location = room1;
	from2to1->location = room2;

	room1->entityElements.push_back(from1to2);
	room2->entityElements.push_back(from2to1);

	Exit* from1to3 = new Exit("Room1to3", "Passage from room 1 to room 3", room1, room3, east, false);
	Exit* from3to1 = new Exit("Room3to1", "A Passage from room 3 to room 1", room3, room1, west, false);

	from1to3->location = room1;
	from3to1->location = room3;

	room1->entityElements.push_back(from1to3);
	room3->entityElements.push_back(from3to1);

	Exit* from2to4 = new Exit("Room2to4", "Passage from room 2 to room 4", room2, room4, north, false);
	Exit* from4to2 = new Exit("Room4to2", "Passage from room 4 to room 2", room4, room2, south, false);

	from2to4->location = room2;
	from4to2->location = room4;

	room2->entityElements.push_back(from2to4);
	room4->entityElements.push_back(from4to2);

	Exit* from3to5 = new Exit("Room3to5", "Passage from room 3 to room 5", room3, room5, north, false);
	Exit* from5to3 = new Exit("Room5to3", "Passage from room 5 to room 3", room5, room3, south, false);

	from3to5->location = room3;
	from5to3->location = room5;

	room3->entityElements.push_back(from3to5);
	room5->entityElements.push_back(from5to3);

	Exit* from1toFinal = new Exit("What lies ahead", "A passage to the unknown", room1, finalRoom, north, false);
	Exit* fromFinalto1 = new Exit("Back to the entrance", "A dark passage", finalRoom, room1, south, false);


	room1->entityElements.push_back(from1toFinal);
	finalRoom->entityElements.push_back(fromFinalto1);

	//Create Items
	Item* dagga = new Item("Dagga", "A small dagga. Sometimes less is more");
	Item* key = new Item("Key", "Old key. Maybe it will take you to your doom");
	Item* note = new Item("Note", "It says \"I can no longer fight that beast...\"");

	dagga->changeLocation(room4);
	key->changeLocation(room5);
	note->changeLocation(room1);

	//Create player
	newPlayer = new Player("Link", "Our hero for this adventure");

	this->worldElements.push_back(newPlayer);

	newPlayer->changeLocation(room1);

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
			else {
				found = false;
			}
			break;
		}
		case 2: {
			if (compareWorld(command[0], "take")) {
				newPlayer->take(command);
			}
			else if (compareWorld(command[0], "drop")) {
				newPlayer->drop(command);
			}
			else {
				found = false;
			}
			break;
		}
		default:
			found = false;
	}
	return found;
}


