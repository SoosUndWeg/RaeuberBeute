//Klasse zum erstellen eines zweidimensionalen Vektors, der alle moeglichen Entity (wie Tiere, Pflanzen, nullEntitys) enthaelt
#include "Map.h"
#include <iostream>

namespace sim {
	//Konstruktor
	Map::Map(int Size) : xSize{ Size }, ySize{ Size }{
		map.resize(xSize, std::vector<Entity*>(ySize, nullptr));
		fill();
		updateAll();
	}
	Map::Map(int xSize, int ySize) : xSize{ xSize }, ySize{ ySize }{
		map.resize(xSize, std::vector<Entity*>(ySize, nullptr));
		fill();
		updateAll();
	}

	//Destruktor
	Map::~Map() {
		//Alle durch "new" erstellten Objekte loeschen
		Entity* buffer = nullptr;
		for (int x = 0; x < xSize; x++) {
			for (int y = 0; y < ySize; y++) {
				if (map[x][y] != nullptr && buffer != map[x][y]) {
					delete map[x][y];
					map[x][y] = nullptr;
				}
				buffer = map[x][y];
			}
		}
	}

	//get
	Entity* Map::getEntity(int _xPos, int _yPos) { return map[_xPos][_yPos]; }

	//set
	void Map::setPos(int _xPos, int _yPos, int _newXPos, int _newYPos) {
		std::swap(map[_xPos][_yPos], map[_newXPos][_newYPos]);

		updateEntity(_newXPos, _newYPos);
		updateEntity(_xPos, _yPos);
	}

	void Map::setXPos(int _xPos, int _yPos, int _newXPos) {
		std::swap(map[_xPos][_yPos], map[_newXPos][_yPos]);

		updateEntity(_newXPos, _yPos);
		updateEntity(_xPos, _yPos);
	}
	
	void Map::setYPos(int _xPos, int _yPos, int _newYPos) {
		std::swap(map[_xPos][_yPos], map[_xPos][_newYPos]);

		map[_xPos][_newYPos] = std::move(map[_xPos][_yPos]);
		map[_xPos][_yPos] = nullEntity;

		updateEntity(_xPos, _newYPos);
		updateEntity(_xPos, _yPos);
	}

	//sonstiges
	void Map::print() {
		Role role;
		for (int y = 0; y < ySize; y++) {
			std::cout << "+---";
		}
		std::cout << "+\n";
		for (int x = 0; x < xSize; x++) {
			for (int y = 0; y < ySize; y++) {
				role = map[x][y]->getRole();
				if (role == predator) {
					std::cout << "| # ";
				}
				else if (role == prey) {
					std::cout << "| x ";
				}
				else if (role == plant) {
					std::cout << "| * ";
				}
				else {
					std::cout << "| O ";
				}
			}
			std::cout << "|\n";
			for (int y = 0; y < ySize; y++) {
				std::cout << "+---";
			}
			std::cout << "+\n";
		}
	}
	void Map::addEntity(Entity* _Entity, int _xPos, int _yPos) {
		_Entity->setXPos(_xPos);
		_Entity->setYPos(_yPos);
		deleteEntity(_xPos, _yPos);
		map[_xPos][_yPos] = _Entity;
	}

	void Map::fill() {
		for (int x = 0; x < xSize; x++) {
			for (int y = 0; y < ySize; y++) {
				nullEntity = new Entity();
				map[x][y] = nullEntity;
			}
		}
	}

	void Map::updateAll() {
		for (int x = 0; x < xSize; x++) {
			for (int y = 0; y < ySize; y++) {
				if (map[x][y] != nullptr) {
					map[x][y]->setPos(x, y);
				}
			}
		}
	}

	void Map::updateEntity(int _xPos, int _yPos) {
		map[_xPos][_yPos]->setPos(_xPos, _yPos);
	}

	void Map::deleteEntity(int _xPos, int _yPos) {
		if (map[_xPos][_yPos] != nullptr) {
			delete map[_xPos][_yPos];
		}
	}
}