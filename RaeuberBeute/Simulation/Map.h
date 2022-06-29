#pragma once
#include "Entity/Entity.h"
#include "Entity/Entities/Predator.h"
#include "Entity/Entities/Prey.h"
#include "Entity/Entities/Plant.h"

#include <iostream>
#include <vector>
#include <random>

namespace sim {
	class Map {
	public:
		//Konstruktor
		Map(int);
		Map(int, int);

		//Destuktor
		~Map();

		//get
		Entity* getEntity(int, int) const;
		int operator[] (int) const;

		//set
		void setPos(int, int, int, int);
		void setXPos(int, int, int);
		void setYPos(int, int, int);

		//sonstiges
		void print();

		//manipulate Entities
		void setEntity(Entity, int, int);
		void fill();
		void updateAll();
		void updateEntity(int, int);
		void deleteEntity(int, int);
		void spawn(Entity, int);
	private:
		std::vector<std::vector<Entity*>> map;

		Entity* nullEntity;

		const int xSize;
		const int ySize;
	};
}