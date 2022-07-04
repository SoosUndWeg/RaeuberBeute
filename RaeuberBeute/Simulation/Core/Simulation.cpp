//TODO Performance testing of everything bruh (vll)
#include "Simulation.h"
#include "../Entity/Entities/Predator.h"
#include "../Entity/Entities/Prey.h"
#include "../Entity/Entities/Plant.h"
#include "../Tools/Random.h"

#include <iomanip>
#include <iostream>
#include <tuple>

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
		map->print();

		for (int y = 0; y < mapYSize; y++) {
			for (int x = 0; x < mapXSize; x++) {
				moveEntity(x, y);
			}
		}
	}
	//Test Map zum haendischen erstellen verschiedener Szenarios zum debuggen
	void Simulation::createTestMap() {
		Predator Fuchs("Fuchs");
		Vision vision("Fuchs vision");
		vision.setRange(3);
		Movement movement("Fuchs movement");
		movement.setRange(1);
		Fuchs.setVision(vision);
		Fuchs.setAttack(Attack());
		Fuchs.setMovement(movement);

		Prey Ente("Ente");
		Ente.setMovement(Movement());
		Ente.setVision(vision);

		Plant Grass("Grass");

		map->setEntity(Fuchs, 0, 1);
		map->setEntity(Fuchs, 9, 0);
		map->setEntity(Fuchs, 1, 1);
		map->setEntity(Fuchs, 5, 2);
		map->setEntity(Fuchs, 8, 8);
		map->setEntity(Fuchs, 9, 9);
		map->setEntity(Fuchs, 11, 7);
		map->setEntity(Fuchs, 10, 8);
		map->setEntity(Fuchs, 11, 8);
		map->setEntity(Fuchs, 5, 9);
		map->setEntity(Ente, 8, 9);
		map->setEntity(Ente, 7, 7);
		map->setEntity(Grass, 4, 4);

		map->print();
		moveEntity(8, 9);
	}

	//Herzstueck der Simulation
	//Entscheiden, was zu tun ist anhand der umliegenden Felder
	void Simulation::moveEntity(int xPos, int yPos) {
		Role role = map->getEntity(xPos, yPos)->getRole();
		
		//***************************Predator*********************
		if (role == predator) {
			//Am Anfang jedes Zuges 1 Essen verlieren
			map->getEntity(xPos, yPos)->starve();

			//Predator toeten, sofern Essen <= 0 ist
			if (map->getEntity(xPos, yPos)->getFoodCount() <= 0) {
				map->setEntity(xPos, yPos);
			}
			else {
				int vision = map->getEntity(xPos, yPos)->getVision()->getRange();
				int movement = map->getEntity(xPos, yPos)->getMovement()->getRange();

				std::pair<int, int> target;
				std::vector<std::pair<int, int>> choicePool;
				std::vector<std::vector<int>> score;

				int highscore = 0;

				int xMin, xMax;
				int yMin, yMax;

				//Schauen, ob Predator genug Essen besitzt, um sich zu vermehren
				if (map->getEntity(xPos, yPos)->getFoodCount() >= 8) {
					//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
					xMin = xPos - 1 < 0 ? 0 : xPos - 1;
					xMax = map->getXSize() - 2 - xPos < 0 ? map->getXSize() - 1 : xPos + 1;
					yMin = yPos - 1 < 0 ? 0 : yPos - 1;
					yMax = map->getYSize() - 2 - yPos < 0 ? map->getYSize() - 1 : yPos + 1;

					score.resize(xMax - xMin, std::vector<int>(yMax - yMin));

					//Nach freien Feldern fuer Nachwuchs suchen
					Role targetRole;
					for(int y = 0; y < yMax - yMin + 1; y++) {
						for (int x = 0; x < xMax - xMin + 1; x++) {
							targetRole = map->getEntity(x + xMin, y + yMin)->getRole();
							score[x][y] = targetRole != prey && targetRole != predator ? 10 : -10;
							highscore = highscore < score[x][y] ? score[x][y] : highscore;
						}
					}
					//Nur vermehren, wenn freies Feld zur Verfuegung steht, sonst nichts machen und naechste Runde abwarten
					if (highscore > 0) {
						//Alle moeglichen Felder zusammenstellen und ein zufaelliges auswaehlen
						for (int y = 0; y < yMax - yMin + 1; y++) {
							for(int x = 0; x < xMax - xMin + 1; x++) {
								if (score[x][y] == highscore)
									choicePool.emplace_back(std::pair<int, int>({ x + xMin, y + yMin}));
							}
						}
						//Zufaelliges Zielfeld auswaehlen
						target = choicePool[sim::Random().ranIntInRange(choicePool.size() - 1)];

						//Vermehren und Essen entsprechend setzen
						map->setEntity(*map->getEntity(xPos, yPos), target.first, target.second);
						map->getEntity(target.first, target.second)->setFoodCount(4);
						map->getEntity(xPos, yPos)->starve(4);
					}
				}
				else {
					//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
					xMin = xPos - vision < 0 ? 0 : xPos - vision;
					xMax = map->getXSize() - 1 - xPos - vision < 0 ? map->getXSize() - 1 : xPos + vision;
					yMin = yPos - vision < 0 ? 0 : yPos - vision;
					yMax = map->getYSize() - 1 - yPos - vision < 0 ? map->getYSize() - 1 : yPos + vision;

					score.resize(xMax - xMin + 1, std::vector<int>(yMax - yMin + 1, 0));

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
								score[x][y] -= 10;
							}
						}
					}
					//Heimat Feld auf neutral setzen
					score[yPos - yMin][xPos - xMin] = 0;

					//Dafuer sorgen, dass der Score-Vector nicht ueber- oder unterschritten wird
					int xMinMove = xPos - xMin - movement < 0 ? 0 : xPos - xMin - movement;
					int xMaxMove = xPos - xMin + movement > xMax - xMin ? xMax - xMin + 1 : xPos - xMin + movement + 1;
					int yMinMove = yPos - yMin - movement < 0 ? 0 : yPos - yMin - movement;
					int yMaxMove = yPos - yMin + movement > yMax - yMin ? yMax - yMin + 1 : yPos - yMin + movement + 1;

					//Highscore aus allen erreichbaren Feldern bestimmen
					for (int y = yMinMove; y < yMaxMove; y++) {
						for (int x = xMinMove; x < xMaxMove; x++) {
							highscore = score[x][y] > highscore ? score[x][y] : highscore;
						}
					}
					//Beste Felder dem Vector hinzufuegen
					for (int y = yMinMove; y < yMaxMove; y++) {
						for (int x = xMinMove; x < xMaxMove; x++) {
							if (score[x][y] == highscore)
								choicePool.emplace_back(std::pair<int, int>{x + xMin, y + yMin});
						}
					}
					//Zufaelliges Feld aus den besten waehlen
					target = choicePool[Random().ranIntInRange(choicePool.size() - 1)];
					
					//Schauen, ob Zielfeld dem aktuellen Feld entspricht
					if (target.first =! xPos && target.second != yPos) {
						//Auf entsprechendes Feld bewegen, eventuell essen
						if (map->getEntity(target.first, target.second)->getRole() == prey) {
							map->getEntity(xPos, yPos)->eat(map->getEntity(target.first, target.second)->getFoodCount());
							map->setPos(xPos, yPos, target.first, target.second);
						}
						else {
							map->setPos(xPos, yPos, target.first, target.second);
							//Wenn das Entity auf dem Zielfeld z.B. eine Pflanze ist, wird sie geloescht
							if (map->getEntity(xPos, yPos)->getRole() != null) {
								map->setEntity(xPos, yPos);
							}
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
		}
		//******************Prey********************************
		else if (role == prey) {
			//Am Anfang jedes Zuges 1 Essen verlieren
			map->getEntity(xPos, yPos)->starve();

			//Predator toeten, sofern Essen <= 0 ist
			if (map->getEntity(xPos, yPos)->getFoodCount() <= 0) {
				map->setEntity(xPos, yPos);
			}
			else {
				int vision = map->getEntity(xPos, yPos)->getVision()->getRange();
				int movement = map->getEntity(xPos, yPos)->getMovement()->getRange();

				std::pair<int, int> target;
				std::vector<std::pair<int, int>> choicePool;
				std::vector<std::vector<int>> score;

				int highscore = 0;

				int xMin, xMax;
				int yMin, yMax;

				//Schauen, ob Prey genug Essen besitzt, um sich zu vermehren
				if (map->getEntity(xPos, yPos)->getFoodCount() >= 8) {
					//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
					xMin = xPos - 1 < 0 ? 0 : xPos - 1;
					xMax = map->getXSize() - 2 - xPos < 0 ? map->getXSize() - 1 : xPos + 1;
					yMin = yPos - 1 < 0 ? 0 : yPos - 1;
					yMax = map->getYSize() - 2 - yPos < 0 ? map->getYSize() - 1 : yPos + 1;

					score.resize(xMax - xMin, std::vector<int>(yMax - yMin));

					//Nach freien Feldern fuer Nachwuchs suchen
					Role targetRole;
					for (int y = 0; y < yMax - yMin + 1; y++) {
						for (int x = 0; x < xMax - xMin + 1; x++) {
							targetRole = map->getEntity(x + xMin, y + yMin)->getRole();
							score[x][y] = targetRole != prey && targetRole != predator ? 10 : -10;
							highscore = highscore < score[x][y] ? score[x][y] : highscore;
						}
					}
					//Nur vermehren, wenn freies Feld zur Verfuegung steht, sonst nichts machen und naechste Runde abwarten
					if (highscore > 0) {
						//Alle moeglichen Felder zusammenstellen und ein zufaelliges auswaehlen
						for (int y = 0; y < yMax - yMin + 1; y++) {
							for (int x = 0; x < xMax - xMin + 1; x++) {
								if (score[x][y] == highscore)
									choicePool.emplace_back(std::pair<int, int>({ x + xMin, y + yMin }));
							}
						}
						//Zufaelliges Zielfeld auswaehlen
						target = choicePool[sim::Random().ranIntInRange(choicePool.size() - 1)];

						//Vermehren und Essen entsprechend setzen
						map->setEntity(*map->getEntity(xPos, yPos), target.first, target.second);
						map->getEntity(target.first, target.second)->setFoodCount(4);
						map->getEntity(xPos, yPos)->starve(4);
					}
				}
				else {
					//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
					xMin = xPos - vision < 0 ? 0 : xPos - vision;
					xMax = map->getXSize() - 1 - xPos - vision < 0 ? map->getXSize() - 1 : xPos + vision;
					yMin = yPos - vision < 0 ? 0 : yPos - vision;
					yMax = map->getYSize() - 1 - yPos - vision < 0 ? map->getYSize() - 1 : yPos + vision;

					score.resize(xMax - xMin + 1, std::vector<int>(yMax - yMin + 1, 0));

					//Felder im Umkreis durchgehen
					for (int y = 0; y < yMax - yMin + 1; y++) {
						for (int x = 0; x < xMax - xMin + 1; x++) {
							if (map->getEntity(x + xMin, y + yMin)->getRole() == plant) {
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
								score[x][y] -= 10;
								if (x > 0)
									score[x - 1][y] -= 2;
								if (x > 0 && y > 0)
									score[x - 1][y - 1] -= 2;
								if (y > 0)
									score[x][y - 1] -= 2;
								if (y > 0 && x < xMax - xMin)
									score[x + 1][y - 1] -= 2;
								if (x < xMax - xMin)
									score[x + 1][y] -= 2;
								if (x < xMax - xMin && y < yMax - yMin)
									score[x + 1][y + 1] -= 2;
								if (y < yMax - yMin)
									score[x][y + 1] -= 2;
								if (x > 0 && y < yMax - yMin)
									score[x - 1][y + 1] -= 2;
							}
							else if (map->getEntity(x + xMin, y + yMin)->getRole() == prey) {
								score[x][y] = -10;
							}
						}
					}
					//Heimat Feld auf neutral setzen
					score[yPos - yMin][xPos - xMin] = 0;

					//Dafuer sorgen, dass der Score-Vector nicht ueber- oder unterschritten wird
					int xMinMove = xPos - xMin - movement < 0 ? 0 : xPos - xMin - movement;
					int xMaxMove = xPos - xMin + movement > xMax - xMin ? xMax - xMin + 1 : xPos - xMin + movement + 1;
					int yMinMove = yPos - yMin - movement < 0 ? 0 : yPos - yMin - movement;
					int yMaxMove = yPos - yMin + movement > yMax - yMin ? yMax - yMin + 1 : yPos - yMin + movement + 1;

					//Highscore aus allen erreichbaren Feldern bestimmen
					for (int y = yMinMove; y < yMaxMove; y++) {
						for (int x = xMinMove; x < xMaxMove; x++) {
							highscore = score[x][y] > highscore ? score[x][y] : highscore;
						}
					}
					//Beste Felder dem Vector hinzufuegen
					for (int y = yMinMove; y < yMaxMove; y++) {
						for (int x = xMinMove; x < xMaxMove; x++) {
							if (score[x][y] == highscore)
								choicePool.emplace_back(std::pair<int, int>{x + xMin, y + yMin});
						}
					}
					//Zufaelliges Feld aus den besten waehlen
					target = choicePool[Random().ranIntInRange(choicePool.size() - 1)];

					//Schauen, ob Zielfeld dem aktuellen Feld entspricht
					if (target.first = !xPos && target.second != yPos) {
						//Auf entsprechendes Feld bewegen, eventuell essen
						if (map->getEntity(target.first, target.second)->getRole() == plant) {
							map->getEntity(xPos, yPos)->eat(map->getEntity(target.first, target.second)->getFoodCount());
							map->setPos(xPos, yPos, target.first, target.second);
						}
						else {
							map->setPos(xPos, yPos, target.first, target.second);
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
		}
	}
}