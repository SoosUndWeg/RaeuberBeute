#include "Map.h"
#include <iostream>
#include <random>

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
				if (buffer != map[x][y]) {
					delete map[x][y];
				}
				buffer = map[x][y];
			}
		}
	}

	//get
	Entity* Map::getEntity(int xPos, int yPos) const { return map[xPos][yPos]; }

	//set
	void Map::setPos(int xPos, int yPos, int newXPos, int newYPos) {
		std::swap(map[xPos][yPos], map[newXPos][newYPos]);

		updateEntity(newXPos, newYPos);
		updateEntity(xPos, yPos);
	}

	void Map::setXPos(int xPos, int yPos, int newXPos) {
		std::swap(map[xPos][yPos], map[newXPos][yPos]);

		updateEntity(newXPos, yPos);
		updateEntity(xPos, yPos);
	}
	
	void Map::setYPos(int xPos, int yPos, int newYPos) {
		std::swap(map[xPos][yPos], map[xPos][newYPos]);

		map[xPos][newYPos] = std::move(map[xPos][yPos]);
		map[xPos][yPos] = nullEntity;

		updateEntity(xPos, newYPos);
		updateEntity(xPos, yPos);
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
				if (map[x][y] != nullptr) {
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
	void Map::setEntity(Entity* entity, int xPos, int yPos) {
		entity->setPos(xPos, yPos);
		deleteEntity(xPos, yPos);
		map[xPos][yPos] = entity;
	}
	void Map::fill() {
		for (int x = 0; x < xSize; x++) {
			for (int y = 0; y < ySize; y++) {
				map[x][y] = nullptr;
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
	void Map::updateEntity(int xPos, int yPos) {
		map[xPos][yPos]->setPos(xPos, yPos);
	}
	void Map::deleteEntity(int xPos, int yPos) {
		if (map[xPos][yPos] != nullptr) {
			delete map[xPos][yPos];
		}
	}
	void Map::spawn(Entity entity, int count) {
		int x;
		int y;
		bool isEmpty;

		if (count < this->xSize * this->ySize) {
			for (int i = 0; i < count; i++) {
				do {
					x = (std::rand() % (this->xSize - 1));
					y = (std::rand() % (this->ySize - 1));
					isEmpty = map[x][y] != nullptr;
					if (!isEmpty) {
						map[x][y] = new Entity(entity);
						std::cout << "Entity bei " << x << ", " << y << " hinzugefuegt." << std::endl;
					}
				} while (isEmpty);
			}
		}
		else {
			std::cerr << "Mehr Elemente versucht zu spawnen, als Platz ist\n";
		}
	}
}