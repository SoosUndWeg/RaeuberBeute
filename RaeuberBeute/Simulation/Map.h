#pragma once
#include "Entity/Entity.h"
#include <vector>

namespace sim {
	class Map {
	public:
		//Konstruktor
		Map(int);
		Map(int, int);

		//Destuktor
		~Map();

		//get
		Entity* getEntity(int, int);

		//set
		void setPos(int, int, int, int);
		void setXPos(int, int, int);
		void setYPos(int, int, int);

		//sonstiges
		void print();
		void addEntity(Entity*, int, int);
		void fill();
		void updateAll();
		void updateEntity(int, int);
		void deleteEntity(int, int);
	private:
		std::vector<std::vector<Entity*>> map;

		Entity* nullEntity;

		int xSize;
		int ySize;
	};
}