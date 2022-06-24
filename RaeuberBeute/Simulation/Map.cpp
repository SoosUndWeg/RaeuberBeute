#include "Map.h"
#include <iostream>

namespace sim {
	//Konstruktor
	Map::Map(int _Size) : xSize{ _Size }, ySize{ _Size }{
		map.resize(xSize, std::vector<Entity*>(ySize, nullptr));
	}
	Map::Map(int _xSize, int _ySize) : xSize{ _xSize }, ySize{ _ySize }{
		map.resize(xSize, std::vector<Entity*>(ySize, nullptr));
	}

	//Destruktor
	Map::~Map() {
		for (int x = 0; x < xSize; x++) {
			for (int y = 0; y < ySize; y++) {
				if (map[x][y] != nullptr) {
					std::cout << "Element [" << x << "][" << y << "] geloescht.\n";
					delete map[x][y];
					map[x][y] = nullptr;
				}
			}
		}
		delete nullEntity;
	}

	//get
	Entity* Map::getEntity(int _xPos, int _yPos) { return map[_xPos][_yPos]; }

	//set
	void Map::setPos(int _xPos, int _yPos, int _newXPos, int _newYPos) {
		map[_xPos][_yPos]->setPos(_newXPos, _newYPos);

		nullEntity = new Entity();

		deleteEntity(_newXPos, _newYPos);

		map[_newXPos][_newYPos] = std::move(map[_xPos][_yPos]);
		map[_xPos][_yPos] = nullEntity;
	}
	//TODO Fix Memory Management
	void Map::setXPos(int _xPos, int _yPos, int _newXPos) {
		map[_xPos][_yPos]->setXPos(_newXPos);
		map[_newXPos][_yPos] = std::move(map[_xPos][_yPos]);
	}
	//TODO Fix Memory Management
	void Map::setYPos(int _xPos, int _yPos, int _newYPos) {
		map[_xPos][_yPos]->setXPos(_newYPos);
		map[_xPos][_newYPos] = std::move(map[_xPos][_yPos]);
	}

	//sonstiges
	void Map::addEntity(Entity* _Entity, int _xPos, int _yPos) {
		_Entity->setXPos(_xPos);
		_Entity->setYPos(_yPos);
		map[_xPos][_yPos] = _Entity;
	}
	void Map::deleteEntity(int _xPos, int _yPos) {
		if (map[_xPos][_yPos] != nullptr) {
			delete map[_xPos][_yPos];
		}
	}
	//TODO add updateEntity function
}