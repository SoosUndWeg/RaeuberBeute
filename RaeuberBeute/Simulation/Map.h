#pragma once

#include "Entity/Entity.h"

#include <vector>
#include <string>
#include <memory>

namespace sim {
	struct Map {
		//Konstruktor
		Map(int);
		Map(int, int);

		//Destuktor
		~Map();

		//get
		std::shared_ptr<Entity> getEntity(int, int) const;
		int getXSize() const;
		int getYSize() const;
		//int operator[] (int) const;

		//set
		void setPos(int, int, int, int);
		void setXPos(int, int, int);
		void setYPos(int, int, int);

		//sonstiges
		void print();

		//manipulate Entities
		void setEntity(int, int);
		void setEntity(Entity, int, int);
		void fill();
		void updateAll();
		void updateEntity(int, int);
		void spawn(Entity, int);
	private:
		std::vector<std::vector<std::shared_ptr<Entity>>> map;

		std::string lineBlueprint = "";
		std::string mapBlueprint = "";

		//Entity* nullEntity;

		const int xSize;
		const int ySize;
	};
}