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
	Room* entrance = new Room("Entrance", "This is the castle's entrance. You can see countless cracks in the wall.\nThe whole building could collapse any minute. Better hurry up!");
	Room* sphinxRoom = new Room("Sphinx's Room", "You are surrounded by a mysterious fog altough you can see almost everything.\nSomething is whispering arround you...");
	Room* armory = new Room("Armory", "From the look of it, it seems it has not been used in ages.\nYou would be lucky to find something useful here.");
	Room* library = new Room("Library", "This room is only accessible after solving the sphinx's riddle.\nIt is said that for each one that tried and failed, there is a book. You counted 66.");
	Room* trollCavern = new Room("Troll's Cavern", "The smell of this cavern stinks so badly that you almost faint.\nIf you wanna succeed, you gotta take down the troll... if not already dead by its stinky smell.");
	Room* courtyard = new Room("Courtyard", "You arrived at the courtyard.\nHere should be the dragon others looked for in the past and the one you are trying to slay.\nYour surroundings are burnt and you can see broken bones all over the place.");

	//Create Items
	Item* dagga = new Item("Dagga", "Small dagga. It will improve your damage if equipped", false, true, true, weapon, 10);
	Item* key = new Item("Key", "Courtyard key. Gift given by the sphinx for those who solve the riddle", false, true, false, other, 0);
	Item* note = new Item("Note", "This was written by the sphinx... \"You have the key, Why don't confont the dragon right now?\"", false, true, false, other, 0);
	Item* box = new Item("Box", "To store some items", true, true, false, other, 0);
	Item* table = new Item("Table", "An old table. It would be perfect to start a bonfire", false, false, false, other, 0);
	Item* sword = new Item("Sword", "A long sword. You can feel a great power stored in it", false, true, true, weapon, 50);
	Item* shield = new Item("Shield", "A old shield. You get the feeling it will save your life", false, true, true, armor, 20);
	Item* healthPotion = new Item("Potion", "Contains an invisible liquid. No one knows what happens after drinking it", false, true, false, potion, 100);
	Item* oldKey = new Item("Old-Key", "You found this key on the entrance. It must unlock doors nearby", false, true, false, other, 0);
	Item* certificate = new Item("Certificate", "This is a certificate saying you have beaten my zork! I hope you had fine playing it. Type quit to close the game", false, true, false, other, 0);

	dagga->changeLocation(library);
	key->changeLocation(box);
	note->changeLocation(box);
	box->changeLocation(library);
	table->changeLocation(entrance);
	healthPotion->changeLocation(armory);

	//Create Creatures
	Creature* troll = new Creature("Troll", "A cavern troll", 100, 20, 20);
	Creature* dragon = new Creature("Dragon", "An unarmored dragon but with lethal hits. Be prepared.", 200, 50, 0);
	Creature* rat = new Creature("Rat", "You can hear something metalic from it.", 10, 10, 0);

	troll->changeLocation(trollCavern);
	sword->changeLocation(troll);
	shield->changeLocation(troll);

	rat->changeLocation(entrance);
	oldKey->changeLocation(rat);

	dragon->changeLocation(courtyard);
	certificate->changeLocation(dragon);

	//Create NPC
	string dialog = 
		"This is your wisdom trial. "
		"Answer my riddle and the way will open. But be aware though only 3 guesses you will have...\n"
		"\"I am the beginning of everything, the end of everywhere.\n I am the beginning of eternity, the end of time and space...\n"
		" What am I?\"\n"
		"I'll be waiting your answer...";

	NPC* sphinx = new NPC("Sphinx", "A lost sphinx. It likes riddles. You should talk to it. Maybe it will help you or kill you. But you really have no choice", 100, 40, 100, dialog, true, "e");
	sphinx->changeLocation(sphinxRoom);

	//Create Connections
	Exit* entranceToSphinx = new Exit("EntranceToSphinx", "There is a heavy fog behind the door. You hear something but can't figure out what it is...", entrance, sphinxRoom, west, true, oldKey);
	Exit* sphinxToEntrance = new Exit("SphinxToEntrance", "A passage through the fog leading to the entrance", sphinxRoom, entrance, east, false, oldKey);

	entranceToSphinx->changeLocation(entrance);
	sphinxToEntrance->changeLocation(sphinxRoom);

	Exit* entranceToArmory = new Exit("EntranceToArmory", "You see spikes, swords, helmets, shields... This door must lead to the armory", entrance, armory, east, true, oldKey);
	Exit* armoryToEntrance = new Exit("ArmoryToEntrance", "This hallway goes back to the entrance", armory, entrance, west, false, oldKey);

	entranceToArmory->changeLocation(entrance);
	armoryToEntrance->changeLocation(armory);

	Exit* sphinxToLibrary = new Exit("SphinxToLibrary", "You get a strange feeling comming from here...", sphinxRoom, library, north, true, NULL);
	Exit* libraryToSphinx = new Exit("LibraryToSphinx", "The whisperings come from the Sphinx's room although you are not sure if the Sphinx is the source...", library, sphinxRoom, south, false, NULL);

	sphinxToLibrary->changeLocation(sphinxRoom);
	libraryToSphinx->changeLocation(library);

	Exit* armoryToCavern = new Exit("ArmoryToCavern", "This is the only way not leading to the entrance. It goes deep and deep...", armory, trollCavern, north, false, NULL);
	Exit* cavernToArmory = new Exit("CavernToArmory", "Leads back to the armory", trollCavern, armory, south, false, NULL);

	armoryToCavern->changeLocation(armory);
	cavernToArmory->changeLocation(trollCavern);

	Exit* entranceToCourtyard = new Exit("EntranceToCourtyard", "You see the courtyard and the dragon. Prepare yourself before entering.", entrance, courtyard, north, true, key);
	Exit* courtyardToEntrance = new Exit("CourtyardToEntrance", "Back to the entrance.", courtyard, entrance, south, false, key);

	entranceToCourtyard->changeLocation(entrance);
	courtyardToEntrance->changeLocation(courtyard);

	//Create player
	newPlayer = new Player("Link", "Our hero for this adventure", 100, 40, 0);

	newPlayer->changeLocation(entrance);

	this->worldElements.push_back(newPlayer);

	this->worldElements.push_back(entrance);
	this->worldElements.push_back(sphinxRoom);
	this->worldElements.push_back(armory);
	this->worldElements.push_back(library);
	this->worldElements.push_back(trollCavern);
	this->worldElements.push_back(courtyard);

	this->worldElements.push_back(entranceToSphinx);
	this->worldElements.push_back(sphinxToEntrance);
	this->worldElements.push_back(entranceToArmory);
	this->worldElements.push_back(armoryToEntrance);
	this->worldElements.push_back(sphinxToLibrary);
	this->worldElements.push_back(libraryToSphinx);
	this->worldElements.push_back(armoryToCavern);
	this->worldElements.push_back(cavernToArmory);
	this->worldElements.push_back(entranceToCourtyard);
	this->worldElements.push_back(courtyardToEntrance);

	this->worldElements.push_back(dagga);
	this->worldElements.push_back(note);
	this->worldElements.push_back(key);
	this->worldElements.push_back(box);
	this->worldElements.push_back(table);
	this->worldElements.push_back(sword);
	this->worldElements.push_back(healthPotion);
	this->worldElements.push_back(shield);
	this->worldElements.push_back(certificate);

	this->worldElements.push_back(troll);
	this->worldElements.push_back(dragon);
	this->worldElements.push_back(rat);

	this->worldElements.push_back(sphinx);
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
			else if (compareWorld(command[0], "help")) {
				newPlayer->showHelp();
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


