#pragma once

#include "Entity/Entity.h"

#include <vector>
#include <string>
#include <memory>

namespace sim {
	struct Map {
		//Konstruktor
		Map(const int&);
		Map(const int&, const int&);

		//Destuktor
		~Map();

		//get
		std::shared_ptr<Entity> getEntity(const int&, const int&) const;
		int getXSize() const;
		int getYSize() const;

		//set
		void setPos(const int&, const int&, const int&, const int&);
		void setXPos(const int&, const int&, const int&);
		void setYPos(const int&, const int&, const int&);

		//sonstiges
		void print();
		void clearMapFromConsole();

		//manipulate Entities
		void setEntity(const int&, const int&);
		void setEntity(const Entity&, const int&, const int&);
		void fill();
		void updateAll();
		void updateEntity(const int&, const int&);
		void spawn(const Entity&, const int&);

		//Einstellung laden
		void loadMapSettings();
		void loadMapSettings(const char*);

		//Einstellungen
		static inline uint16_t map_spawn_retry_max = 40;
	private:
		std::vector<std::vector<std::shared_ptr<Entity>>> map;

		std::string lineBlueprint = "";
		std::string mapBlueprint = "";

		//Entity* nullEntity;

		const int xSize;
		const int ySize;
	};
}