#pragma once
#include "Entity.h"
#include <vector>
#include "Player.h"

using namespace std;


class World
{
	public:
		World();
		~World();

		void createWorld();

		void showRoomsDescriptions();

		void showWorldElements();

		bool executeCommand(vector<string>& command);

	private:

		vector<Entity*> worldElements;
		Player* newPlayer;

};

