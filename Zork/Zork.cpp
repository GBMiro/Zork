// Zork.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <conio.h>
#include <vector>
#include "World.h"
#include "utils.h"
using namespace std;

int main()
{
    cout << "Welcome to my Zork!\n";
	cout << "This game was implemented for the accessing test to the UPC's Masters degree in Advanced Programming for AAA videogames. I hope you have fun playing it!" << endl;
	World myZorkWorld = World();


	cout << "\n----------------------------\n" << endl;
	cout << "THE LAST FIGHT" << endl;

	cout << "Your village town has always been living under the tirany of the dragons living in the valley. Your people have suffered countless losses, not only human." << endl;
	cout << "But years ago, their numbers were reduced to just one. Many tried to kill it, but none succeded." << endl;
	cout << "You find yourself in the castle where all of them used to live to slay the last one and free your village from their tirany...\n\n" << endl;

	bool gameOnGoing = true;

	char nextChar;

	string line = "";

	vector<string> command;

	command.push_back("look");

	while (gameOnGoing) {

		if (_kbhit() != 0) {

			nextChar = _getch();

			if (nextChar == '\r') {
				size_t pos = 0;
				string word;
				string delimiter = " ";

				while ((pos = line.find(delimiter)) != string::npos) {
					word = line.substr(0, pos);
					line.erase(0, pos + delimiter.length());
					command.push_back(word);
				}
				command.push_back(line); // Last word
				cout << endl;
			}
			else if (nextChar == '\b') { //Backspace found
				if (line.length() > 0) {
					line.pop_back();
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else {
				line += nextChar;
				cout << nextChar;
			}
		}

		if (command.size() > 0 && compare(command[0], "quit")) {
			break;
		}

		if (command.size() > 0 && !myZorkWorld.executeCommand(command)) {
			cout << "Sorry this command does not exist. Type \"help\" to see an available command list" << endl;
		}

		if (command.size() > 0) {
			line = "";
			command.clear();
			gameOnGoing = myZorkWorld.worldTurn();
		}
	}

	cout << "Thank you for playing!" << endl;
}