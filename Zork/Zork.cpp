// Zork.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <conio.h>
#include <vector>
#include "World.h"
using namespace std;

bool compare(const string& first, const string& second) {
	return _stricmp(first.c_str(), second.c_str()) == 0;
}

int main()
{
    cout << "Welcome to my Zork!\n";
	World myZorkWorld = World();

	//myZorkWorld.showRoomsDescriptions();

	cout << "----------------------------" << endl;

	//myZorkWorld.showWorldElements();

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

	cout << "Thank you for playing." << endl;
}



// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
