#include "Map.h"

namespace sim {
	//Konstruktor
	Map::Map(int _Size) : xSize{ _Size }, ySize{ _Size }{ map.resize(xSize, std::vector<Entity>(ySize)); }
	Map::Map(int _xSize, int _ySize) : xSize{ _xSize }, ySize{ _ySize }{ map.resize(xSize, std::vector<Entity>(ySize)); }

	Entity Map::getEntity(int _xPos, int _yPos) {
		Entity _Entity = map[_xPos][_yPos];
		return map[_xPos][_yPos];
	}

	void Map::addEntity(Entity _Entity, int _xPos, int _yPos) {
		_Entity.setXPos(_xPos);
		_Entity.setYPos(_yPos);
		map[_xPos][_yPos] = _Entity;
	}
}