#include "Map.h"

#include "Tools/Random.h"
#include "Tools/Tools.h"

#include <iostream>

namespace sim {
	//Konstruktor
	Map::Map(const int& Size) : xSize{ Size }, ySize{ Size }{
		//Blaupause für die Ausgabe erstellen, um Leistung zu sparen
		for (int x = 0; x < xSize; x++) {
			lineBlueprint += "+---";
		}
		lineBlueprint += "+\n";

		//Blaupause für das leeren der Konsole erstellen, um Leistung zu sparen
		sim::createClearBlueprint(std::string(lineBlueprint + "+-> X\n").length(), ySize * 2 + 4);

		//Map initialisieren
		map.resize(Size, std::vector<std::shared_ptr<Entity>>(Size, nullptr));
		fill();
		updateAll();
	}
	Map::Map(const int& xSize, const int& ySize) : xSize{ xSize }, ySize{ ySize }{
		//Blaupause für die Ausgabe erstellen, um Leistung zu sparen
		for (int x = 0; x < xSize; x++) {
			lineBlueprint += "+---";
		}
		lineBlueprint += "+\n";

		//Blaupause für das leeren der Konsole erstellen, um Leistung zu sparen
		sim::createClearBlueprint(std::string(lineBlueprint + "+-> X\n").length(), ySize * 2 + 4);

		//Map initialisieren
		map.resize(xSize, std::vector<std::shared_ptr<Entity>>(ySize, nullptr));
		fill();
		updateAll();
	}

	//Destruktor
	Map::~Map() {}

	//get
	std::shared_ptr<Entity> Map::getEntity(const int& xPos, const int& yPos) const { return this->map[xPos][yPos]; }
	int Map::getXSize() const { return this->xSize; }
	int Map::getYSize() const { return this->ySize; }
	//int Map::operator[] (int xPos) const { return 1; }

	//set
	void Map::setPos(const int& xPos, const int& yPos, const int& newXPos, const int& newYPos) {
		std::swap(map[xPos][yPos], map[newXPos][newYPos]);

		updateEntity(newXPos, newYPos);
		updateEntity(xPos, yPos);
	}

	void Map::setXPos(const int& xPos, const int& yPos, const int& newXPos) {
		std::swap(map[xPos][yPos], map[newXPos][yPos]);

		updateEntity(newXPos, yPos);
		updateEntity(xPos, yPos);
	}
	
	void Map::setYPos(const int& xPos, const int& yPos, const int& newYPos) {
		std::swap(map[xPos][yPos], map[xPos][newYPos]);

		updateEntity(xPos, newYPos);
		updateEntity(xPos, yPos);
	}

	//sonstiges
	void Map::print() {
		Role role;
		mapBlueprint = "";
		for (int x = 0; x < xSize; x++) {
			mapBlueprint += "+---";
		}
		mapBlueprint += "+-> X\n";
		for (int y = 0; y < ySize; y++) {
			for (int x = 0; x < xSize; x++) {
				role = map[x][y]->getRole();
				if (role == predator) {
					mapBlueprint += "| # ";
				}
				else if (role == prey) {
					mapBlueprint += "| x ";
				}
				else if (role == plant) {
					mapBlueprint += "| * ";
				}
				else {
					mapBlueprint += "|   ";
				}
			}
			mapBlueprint += ("|\n" + lineBlueprint);
		}
		mapBlueprint += "|\nV\nY";
		std::cout << mapBlueprint << std::endl;
	}
	//Entsprechend viele Zeilen mit entsprechender länge aus der Konsole entfernen, wie die Map groß ist
	void Map::clearMapFromConsole() {
		sim::clearByBlueprint();
	}

	//manipulate Entities
	void Map::setEntity(const int& xPos, const int& yPos) {
		map[xPos][yPos] = std::make_shared<Entity>(Entity());
		updateEntity(xPos, yPos);
	}
	void Map::setEntity(const Entity& entity, const int& xPos, const int& yPos) {
		map[xPos][yPos] = std::make_shared<Entity>(entity);
		updateEntity(xPos, yPos);
	}
	void Map::fill() {
		for (int y = 0; y < ySize; y++) {
			for (int x = 0; x < xSize; x++) {
				map[x][y] = std::make_shared<Entity>(Entity());
			}
		}
	}
	void Map::updateAll() {
		for (int y = 0; y < ySize; y++) {
			for (int x = 0; x < xSize; x++) {
				if (map[x][y] != nullptr)
					map[x][y]->setPos(x, y);
			}
		}
	}
	void Map::updateEntity(const int& xPos, const int& yPos) {
		map[xPos][yPos]->setPos(xPos, yPos);
	}

	//Entities auf der Map spawnen
	void Map::spawn(const Entity& entity, const int& count) {
		int x;
		int y;
		//Um zu verhindern, dass die Schleife unendlich laeuft, sobald die Map sehr voll oder komplett voll ist
		int breakCondition = 0;
		bool isEmpty;

		if (count < this->xSize * this->ySize) {
			for (int i = 0; i < count; i++) {
				do {
					breakCondition++;
					x = sim::Random().ranIntInRange(this->xSize - 1);
					y = sim::Random().ranIntInRange(this->ySize - 1);

					isEmpty = map[x][y]->getRole() != null;
					if (!isEmpty) {
						map[x][y] = std::make_shared<Entity>(entity);
					}
				} while (isEmpty && (breakCondition < 20));
			}
		}
		else {
			std::cerr << "Mehr Elemente versucht zu spawnen, als Platz ist\n";
		}
		updateAll();
	}
}