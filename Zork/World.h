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

		bool executeCommand(vector<string>& command);

		void worldTurn();

	private:

		vector<Entity*> worldElements;
		Player* player;

};

