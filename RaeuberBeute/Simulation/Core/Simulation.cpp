//TODO Performance testing of everything bruh (vll)
#include "Simulation.h"
#include <iomanip>

namespace sim {
	//Konstruktor
	Simulation::Simulation() : mapXSize{ 10 }, mapYSize{ 10 } {
		map = new Map(10);
	}
	Simulation::Simulation(int mapSize) : mapXSize{ mapSize }, mapYSize{ mapSize } {
		map = new Map(mapSize);
	}
	Simulation::Simulation(int mapXSize, int mapYSize) : mapXSize{ mapXSize }, mapYSize{ mapYSize } {
		map = new Map(mapXSize, mapYSize);
	}

	//Destruktor
	Simulation::~Simulation() {
		delete map;
	}

	void Simulation::createDefaultMap() {
		Predator Fuchs("Fuchs");
		Fuchs.setVision(Vision());
		Fuchs.setAttack(Attack());
		Fuchs.setMovement(Movement());

		Prey Ente("Ente");
		Ente.setMovement(Movement());
		Ente.setVision(Vision());

		Plant Grass("Grass");

		map->spawn(Fuchs, mapXSize);
		map->spawn(Ente, mapXSize);
		map->spawn(Grass, mapYSize * 2);

		std::cout << "Alles gespawnt" << std::endl;
		map->print();
		std::cout << "Fertig ausgegeben\n";
	}

	void Simulation::createTestMap() {
		Predator Fuchs("Fuchs");
		Vision vision("Fuchs vision");
		vision.setRange(3);
		Movement movement("Fuchs movement");
		movement.setRange(2);
		Fuchs.setVision(vision);
		Fuchs.setAttack(Attack());
		Fuchs.setMovement(movement);

		std::cout << "Movement Range: " << Fuchs.getMovement()->getRange() << std::endl;

		std::cout << "Vision Range: " << Fuchs.getVision()->getRange() << std::endl;

		Prey Ente("Ente");
		Ente.setMovement(Movement());
		Ente.setVision(Vision());

		Plant Grass("Grass");

		map->setEntity(Fuchs, 0, 1);
		map->setEntity(Fuchs, 9, 0);
		map->setEntity(Fuchs, 1, 1);
		map->setEntity(Fuchs, 14, 2);
		map->setEntity(Fuchs, 8, 8);
		map->setEntity(Fuchs, 9, 9);
		map->setEntity(Ente, 8, 9);
		map->setEntity(Ente, 7, 7);
		map->setEntity(Grass, 4, 4);

		map->print();
		moveEntity(9, 9);

		std::cout << "Ende von Simulation::createTestMap()" << std::endl;
	}

	//***Herzstueck der Simulation***
	//Logik der Entscheidung
	//Suche Felder in Sichtweite ab und bewerte, wie gut sie sind
	void Simulation::moveEntity(int xPos, int yPos) {
		Role role = map->getEntity(xPos, yPos)->getRole();
		std::vector<std::vector<int>> score;
		int highscore = 0;

		int xMin, xMax;
		int yMin, yMax;
			  
		if (role == predator) {
			//Am Anfang jedes Zuges 1 Essen verlieren
			map->getEntity(xPos, yPos)->starve();
			//Predator toeten, sofern Essen <= 0 ist
			if (map->getEntity(xPos, yPos)->getFoodCount() <= 0) {
				map->deleteEntity(xPos, yPos);
				map->setEntity(xPos, yPos);
			}
			else {
				//Schauen, ob Predator genug Essen besitzt, um sich zu vermehren
				if (map->getEntity(xPos, yPos)->getFoodCount() >= 8) {

				}
				else {
					int vision = map->getEntity(xPos, yPos)->getVision()->getRange();
					int movement = map->getEntity(xPos, yPos)->getMovement()->getRange();

					std::cout << "xPos: " << xPos << ", yPos: " << yPos << ", vision: " << vision << std::endl;

					//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
					xMin = xPos - vision < 0 ? 0 : xPos - vision;
					xMax = map->getXSize() - 1 - xPos - vision < 0 ? map->getXSize() - 1 : xPos + vision;
					yMin = yPos - vision < 0 ? 0 : yPos - vision;
					yMax = map->getYSize() - 1 - yPos - vision < 0 ? map->getYSize() - 1 : yPos + vision;

					//Wie schon in map muss bei direktem Zugriff auf score x und y vertauscht werden (score[y][x] = ...)
					score.resize(yMax - yMin + 1, std::vector<int>(xMax - xMin + 1, 0));

					std::cout << xMin << ", " << xMax << ", " << yMin << ", " << yMax << std::endl;

					//Felder im Umkreis durchgehen
					for (int y = 0; y < yMax - yMin + 1; y++) {
						for (int x = 0; x < xMax - xMin + 1; x++) {
							if (map->getEntity(x + xMin, y + yMin)->getRole() == prey) {
								//Score von dem Feld und den umliegenden Feldern hochsetzen
								score[x][y] += 4;
								if (x > 0)
									score[x - 1][y] += 1;
								if (x > 0 && y > 0)
									score[x - 1][y - 1] += 1;
								if (y > 0)
									score[x][y - 1] += 1;
								if (y > 0 && x < xMax - xMin)
									score[x + 1][y - 1] += 1;
								if (x < xMax - xMin)
									score[x + 1][y] += 1;
								if (x < xMax - xMin && y < yMax - yMin)
									score[x + 1][y + 1] += 1;
								if (y < yMax - yMin)
									score[x][y + 1] += 1;
								if (x > 0 && y < yMax - yMin)
									score[x - 1][y + 1] += 1;
							}
							else if (map->getEntity(x + xMin, y + yMin)->getRole() == predator) {
								score[y][x] -= 10;
							}
						}
					}
					//Heimat Feld auf neutral setzen
					score[yPos - yMin][xPos - xMin] = 0;

					//Dafuer sorgen, dass der Score-Vector nicht ueber- oder unterschritten wird
					int xMinMove = xPos - xMin - movement < 0 ? 0 : xPos - xMin - movement;
					int xMaxMove = xPos - xMin + movement > xMax - xMin ? xMax - xMin + 1 : xPos - xMin + movement + 1;
					int yMinMove = yPos - yMin - movement < 0 ? 0 : yPos - yMin - movement;
					int yMaxMove = yPos - yMin + movement > yMax - yMin ? yMax - xMin + 1 : yPos - yMin + movement + 1;

					std::cout << "xMinMove: " << xMinMove << ", xMaxMove: " << xMaxMove << ", yMinMove: " << yMinMove << ", yMaxMove: " << yMaxMove << "\n";
					//Highscore aus allen erreichbaren Feldern bestimmen
					std::vector<std::pair<int, int>> choicePool;
					for (int y = yMinMove; y < yMaxMove; y++) {
						for (int x = xMinMove; x < xMaxMove; x++) {
							highscore = score[x][y] > highscore ? score[x][y] : highscore;
						}
					}
					std::cout << "Highscore: " << highscore << std::endl;
					//Beste Felder dem Vector hinzufuegen
					for (int y = yMinMove; y < yMaxMove; y++) {
						for (int x = xMinMove; x < xMaxMove; x++) {
							if (score[x][y] == highscore)
								choicePool.emplace_back(std::pair<int, int>{x + xMin, y + yMin});
						}
					}
					//Zufaelliges Feld aus den besten waehlen
					std::pair<int, int> target = choicePool[Random().ranIntInRange(choicePool.size() - 1)];
					std::cout << "Groesse des Choice-Pools: " << choicePool.size() << ", zufaellig ausgewaehlt wurde: x=" << target.first << ", y=" << target.second << std::endl;

					//Schauen, ob Zielfeld dem aktuellen Feld entspricht
					if (target.first =! xPos && target.second != yPos) {
						//Auf entsprechendes Feld bewegen, eventuell essen
						if (map->getEntity(target.first, target.second)->getRole() == prey) {
							map->getEntity(xPos, yPos)->eat(map->getEntity(target.first, target.second)->getFoodCount());
							map->setPos(xPos, yPos, target.first, target.second);
							map->deleteEntity(xPos, yPos);
						}
						else {
							map->setPos(xPos, yPos, target.first, target.second);
							//Wenn das Entity auf dem Zielfeld z.B. eine Pflanze ist, wird sie geloescht
							if (map->getEntity(xPos, yPos)->getRole() != null) {
								map->deleteEntity(xPos, yPos);
								map->setEntity(xPos, yPos);
							}
						}
					}
					else {
						std::cout << "Zielfeld entspricht aktuellem Feld\n";
					}
				}
			}

			for (int y = 0; y < yMax - yMin + 1; y++) {
				for (int x = 0; x < xMax - xMin + 1; x++) {
					std::cout << "+---";
				}
				std::cout << "+\n";
				for (int x = 0; x < xMax - xMin + 1; x++) {
					std::cout << "|" << std::setw(3) << score[x][y];
				}
				std::cout << "|\n";
			}
			for (int x = 0; x < xMax - xMin + 1; x++) {
				std::cout << "+---";
			}
			std::cout << "+\n";
		}
		else if (role == prey) {
			//Prey p((*map->getPrey));

		}

		
	}
}