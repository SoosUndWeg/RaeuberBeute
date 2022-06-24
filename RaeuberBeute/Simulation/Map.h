#pragma once
#include "Entity/Entity.h"
#include <vector>

namespace sim {
	class Map {
	public:
		Map(int);
		Map(int, int);

		Entity getEntity(int, int);

		void addEntity(Entity, int, int);
	private:
		std::vector<std::vector<Entity>> map;

		Entity nullEntity;

		int xSize;
		int ySize;
	};
}