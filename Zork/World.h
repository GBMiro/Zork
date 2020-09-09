#pragma once
#include "Entity.h"
#include <vector>

using namespace std;


class World
{
	public:
		World();
		~World();

		void createWorld();

		void showRoomsDescriptions();

		void showWorldElements();

	private:
		vector<Entity*> worldElements;

};

