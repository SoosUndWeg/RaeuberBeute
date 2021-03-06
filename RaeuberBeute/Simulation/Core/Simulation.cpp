#include "Simulation.h"

#include "../Entity/Entities/Predator.h"
#include "../Entity/Entities/Prey.h"
#include "../Entity/Entities/Plant.h"
#include "../Tools/Random.h"
#include "../Tools/Tools.h"

#include <iomanip>
#include <iostream>
#include <tuple>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

namespace sim {
	//Konstruktor
	Simulation::Simulation() : mapXSize{ 10 }, mapYSize{ 10 }, simulationNumber{ simulationCount } {
		map = new Map(10);
		//Datei fuer Ausgabe oeffnen und sicherstellen, dass sie erfolgreich geoeffnet wurde
		fileStream.open("simulation_data_" + std::to_string(simulationNumber) + ".txt");
		if (!fileStream.is_open())
			print_file = false;

		//Standart Anzahl fuer Entitys setzten, abhaengig von der Mapgroesse (von der laengsten Seite)
		if(predator_quantity == 0)
			predator_quantity = mapXSize < mapYSize ? mapYSize : mapXSize;
		if(prey_quantity == 0)
			prey_quantity = mapXSize < mapYSize ? mapYSize : mapXSize;
		if(plant_quantity == 0)
			plant_quantity = mapXSize < mapYSize ? mapYSize * 2 : mapXSize * 2;

		//Anzahl der Simulationen hochsetzen
		simulationCount++;
	}
	Simulation::Simulation(const int& mapSize) : mapXSize{ mapSize }, mapYSize{ mapSize }, simulationNumber{ simulationCount } {
		map = new Map(mapSize);
		//Datei fuer Ausgabe oeffnen und sicherstellen, dass sie erfolgreich geoeffnet wurde
		fileStream.open("simulation_data_" + std::to_string(simulationNumber) + ".txt");
		if (!fileStream.is_open())
			print_file = false;

		//Standart Anzahl fuer Entitys setzten, abhaengig von der Mapgroesse (von der laengsten Seite)
		if (predator_quantity == 0)
			predator_quantity = mapXSize < mapYSize ? mapYSize : mapXSize;
		if (prey_quantity == 0)
			prey_quantity = mapXSize < mapYSize ? mapYSize : mapXSize;
		if (plant_quantity == 0)
			plant_quantity = mapXSize < mapYSize ? mapYSize * 2 : mapXSize * 2;

		//Anzahl der Simulationen hochsetzen
		simulationCount++;
	}
	Simulation::Simulation(const int& mapXSize, const int& mapYSize) : mapXSize{ mapXSize }, mapYSize{ mapYSize }, simulationNumber{ simulationCount } {
		map = new Map(mapXSize, mapYSize);
		//Datei fuer Ausgabe oeffnen und sicherstellen, dass sie erfolgreich geoeffnet wurde
		fileStream.open("simulation_data_" + std::to_string(simulationNumber) + ".txt");
		if (!fileStream.is_open())
			print_file = false;

		//Standart Anzahl fuer Entitys setzten, abh?ngig von der Mapgroesse (von der Laengsten Seite)
		if (predator_quantity == 0)
			predator_quantity = mapXSize < mapYSize ? mapYSize : mapXSize;
		if (prey_quantity == 0)
			prey_quantity = mapXSize < mapYSize ? mapYSize : mapXSize;
		if (plant_quantity == 0)
			plant_quantity = mapXSize < mapYSize ? mapYSize * 2 : mapXSize * 2;

		//Anzahl der Simulationen hochsetzen
		simulationCount++;
	}

	//Destruktor
	Simulation::~Simulation() {
		delete map;
		fileStream.close();
	}

	void Simulation::createDefaultMap() {
		//Objekt "fuchs" vom Typ "predator" erstellen und Eigenschaften zuweisen
		Predator fuchs("Fuchs");
		Vision predatorVision;
		predatorVision.setRange(predator_vision_range);
		Movement predatorMovement;
		predatorMovement.setRange(predator_movement_range);
		fuchs.setVision(predatorVision);
		fuchs.setAttack(Attack());
		fuchs.setMovement(predatorMovement);

		//Objekt "ente" vom Typ "prey" erstellen und Eigenschaften zuweisen
		Prey ente("Ente");
		Vision preyVision;
		preyVision.setRange(prey_vision_range);
		Movement preyMovement;
		preyMovement.setRange(prey_movement_range);
		ente.setMovement(preyMovement);
		ente.setVision(preyVision);

		//Objekt "grass" vom Typ "plant" erstellen und Eigenschaften zuweisen
		Plant grass("Grass");
		grass.setFoodCount(plant_food_count);

		//Entities spawnen
		map->spawn(fuchs, predator_quantity);
		map->spawn(ente, prey_quantity);
		map->spawn(grass, plant_quantity);

		//Alle Entities dem Tracker hinzufuegen
		updateEntityTracker();
		
		sim::clearConsole();
	}
	//Test Map zum haendischen erstellen verschiedener Szenarios zum debuggen
	void Simulation::createTestMap() {
		Predator Fuchs("Fuchs");
		Vision vision("Fuchs vision");
		vision.setRange(1);
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

		updateEntityTracker();
	}

	//Schritt in der Simulation machen
	void Simulation::step() {
		for (std::weak_ptr<Entity> tmp_weak_ptr : entityTracker) {
			if (std::shared_ptr<Entity> tmp_shared_ptr = tmp_weak_ptr.lock()) {
				if((tmp_shared_ptr->getRole() != null) && (tmp_shared_ptr->getRole() != plant))
					moveEntity(tmp_shared_ptr->getXPos(), tmp_shared_ptr->getYPos());
			}
		}

		if (plants_respawn) {
			Plant plant;
			plant.setFoodCount(plant_food_count);
			map->spawn(plant, plant_quantity - getRoleCount(sim::plant));
		}

		//Nach ausgewaehlten Optionen in Datei oder Konsole ausgeben
		printStep();
		//Liste mit weak_ptr, die auf Entitys zeigen, updaten
		updateEntityTracker();
		//Schrittzaehler eins hochsetzen
		steps++;
	}
	void Simulation::run(const int& steps) {
		//sim::clearConsole();
		for (int i = 0; i < steps; i++)
			step();
	}

	//Herzstueck der Simulation
	//Entscheiden, was zu tun ist anhand der umliegenden Felder
	void Simulation::moveEntity(const int& xPos, const int& yPos) {
		Role role = map->getEntity(xPos, yPos)->getRole();
		
		//***************************Predator*********************
		if (role == predator) {
			//Am Anfang jedes Zuges 1 Essen verlieren
			map->getEntity(xPos, yPos)->starve();

			//Predator toeten, sofern Essen <= 0 ist
			if (map->getEntity(xPos, yPos)->getFoodCount() <= 0) {
				map->setEntity(xPos, yPos);
			}
			//Predator toeten, sofern zu alt
			else if (map->getEntity(xPos, yPos)->getAge() > predator_max_age) {
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
				if (map->getEntity(xPos, yPos)->getFoodCount() >= predator_reproduction_threshold) {
					//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
					xMin = xPos - 1 < 0 ? 0 : xPos - 1;
					xMax = map->getXSize() - 2 - xPos < 0 ? map->getXSize() - 1 : xPos + 1;
					yMin = yPos - 1 < 0 ? 0 : yPos - 1;
					yMax = map->getYSize() - 2 - yPos < 0 ? map->getYSize() - 1 : yPos + 1;

					score.resize(xMax - xMin + 1, std::vector<int>(yMax - yMin + 1));

					//Nach freien Feldern fuer Nachwuchs suchen
					Role targetRole;
					for(int y = 0; y < yMax - yMin + 1; y++) {
						for (int x = 0; x < xMax - xMin + 1; x++) {
							targetRole = map->getEntity(x + xMin, y + yMin)->getRole();
							score[x][y] = (targetRole != prey) && (targetRole != predator) ? 10 : (- 10);
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
						map->getEntity(xPos, yPos)->starve(predator_reproduction_cost);
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
					score[xPos - xMin][yPos - yMin] = 0;

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
					if (choicePool.size() > 0)
						target = choicePool[Random().ranIntInRange(choicePool.size() - 1)];
					else
						target = { xPos, yPos };
					
					//Schauen, ob Zielfeld dem aktuellen Feld entspricht
					if (((target.first != xPos) || (target.second != yPos))) {
						//Auf entsprechendes Feld bewegen, eventuell essen
						if (map->getEntity(target.first, target.second)->getRole() == prey) {
							map->getEntity(xPos, yPos)->eat(map->getEntity(target.first, target.second)->getFoodCount());
							map->setPos(xPos, yPos, target.first, target.second);
							map->setEntity(xPos, yPos);
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
				//Score Map ausgeben
				if (print_console && print_console_score_map && !print_console_animation_create) {
					std::cout << "Predator [" << xPos << "][" << yPos << "]\n";
					for (int y = 0; y < score[0].size(); y++) {
						for (int x = 0; x < score.size(); x++) {
							std::cout << "+---";
						}
						std::cout << "+\n";
						for (int x = 0; x < score.size(); x++) {
							std::cout << "|" << std::setw(3) << score[x][y];
						}
						std::cout << "|\n";
					}
					for (int x = 0; x < score.size(); x++) {
						std::cout << "+---";
					}
					std::cout << "+\n";
				}
			}
			//Map nach jeder einzelnen Bewegung in der Konsole ausgeben
			if (print_console && (print_console_detailed_map || print_console_animation_create)) {
				if(!print_console_score_map && !print_console_animation_create)
					std::cout << "Predator [" << xPos << "][" << yPos << "]\n";
				if (print_console_animation_create) {
					std::this_thread::sleep_for(std::chrono::milliseconds(print_console_animation_pause_ms));
					if (use_VT100_escape_sequence)
						map->clearMapFromConsole();
					else
						sim::clearConsole();
				}
				map->print();
			}
			if (print_file) {
				//Vollstaendige Map in Datei schreiben
				if (print_file_positions_detailed) {
					for (int y = 0; y < mapYSize; y++) {
						for (int x = 0; x < mapXSize; x++) {
							fileStream << steps << " " << map->getEntity(x, y)->getRole() << " " << x << " " << y << " ";
						}
						fileStream << "\n";
					}
				}
				//Position aller Entitys, die nicht null sind, in datei schreiben
				else if (print_file_positions_detailed_compressed) {
					for (int y = 0; y < mapYSize; y++) {
						for (int x = 0; x < mapXSize; x++) {
							if (map->getEntity(x, y)->getRole() != null)
								fileStream << steps << " " << map->getEntity(x, y)->getRole() << " " << x << " " << y << " ";
						}
					}
					fileStream << "\n";
				}
			}
		}
		//******************Prey********************************
		else if (role == prey) {
			//Am Anfang jedes Zuges 1 Essen verlieren
			map->getEntity(xPos, yPos)->starve();

			//Prey toeten, sofern Essen <= 0 ist
			if (map->getEntity(xPos, yPos)->getFoodCount() <= 0) {
				map->setEntity(xPos, yPos);
			}
			//Prey toeten, sofern zu alt
			else if (map->getEntity(xPos, yPos)->getAge() > prey_max_age) {
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
				if (map->getEntity(xPos, yPos)->getFoodCount() >= prey_reproduction_threshold) {
					//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
					xMin = xPos - 1 < 0 ? 0 : xPos - 1;
					xMax = map->getXSize() - 2 - xPos < 0 ? map->getXSize() - 1 : xPos + 1;
					yMin = yPos - 1 < 0 ? 0 : yPos - 1;
					yMax = map->getYSize() - 2 - yPos < 0 ? map->getYSize() - 1 : yPos + 1;

					score.resize(xMax - xMin + 1, std::vector<int>(yMax - yMin + 1));

					//Nach freien Feldern fuer Nachwuchs suchen
					Role targetRole;
					for (int y = 0; y < yMax - yMin + 1; y++) {
						for (int x = 0; x < xMax - xMin + 1; x++) {
							targetRole = map->getEntity(x + xMin, y + yMin)->getRole();
							score[x][y] = (targetRole != prey) && (targetRole != predator) ? 10 : -10;
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
						map->getEntity(xPos, yPos)->starve(prey_reproduction_cost);
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
									score[x - 1][y] -= 5;
								if (x > 0 && y > 0)
									score[x - 1][y - 1] -= 5;
								if (y > 0)
									score[x][y - 1] -= 5;
								if (y > 0 && x < xMax - xMin)
									score[x + 1][y - 1] -= 5;
								if (x < xMax - xMin)
									score[x + 1][y] -= 5;
								if (x < xMax - xMin && y < yMax - yMin)
									score[x + 1][y + 1] -= 5;
								if (y < yMax - yMin)
									score[x][y + 1] -= 5;
								if (x > 0 && y < yMax - yMin)
									score[x - 1][y + 1] -= 5;
							}
							else if (map->getEntity(x + xMin, y + yMin)->getRole() == prey) {
								score[x][y] = -10;
							}
						}
					}
					//Heimat Feld auf neutral setzen
					score[xPos - xMin][yPos - yMin] = 0;

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
					if (choicePool.size() > 0)
						target = choicePool[Random().ranIntInRange(choicePool.size() - 1)];
					else
						target = { xPos, yPos };

					//Schauen, ob Zielfeld dem aktuellen Feld entspricht
					if (((target.first != xPos) || (target.second != yPos))) {
						//Auf entsprechendes Feld bewegen, eventuell essen
						if (map->getEntity(target.first, target.second)->getRole() == plant) {
							map->getEntity(xPos, yPos)->eat(map->getEntity(target.first, target.second)->getFoodCount());
							map->setPos(xPos, yPos, target.first, target.second);
							map->setEntity(xPos, yPos);
						}
						else {
							map->setPos(xPos, yPos, target.first, target.second);
						}
					}
				}
				//Score Map ausgeben
				if (print_console && print_console_score_map && !print_console_animation_create) {
					std::cout << "Prey [" << xPos << "][" << yPos << "]\n";
					for (int y = 0; y < score[0].size(); y++) {
						for (int x = 0; x < score.size(); x++) {
							std::cout << "+---";
						}
						std::cout << "+\n";
						for (int x = 0; x < score.size(); x++) {
							std::cout << "|" << std::setw(3) << score[x][y];
						}
						std::cout << "|\n";
					}
					for (int x = 0; x < score.size(); x++) {
						std::cout << "+---";
					}
					std::cout << "+\n";
				}
			}
			//Map nach jeder einzelnen Bewegung ausgeben
			if (print_console && (print_console_detailed_map || print_console_animation_create)) {
				if(!print_console_score_map && !print_console_animation_create)
					std::cout << "Prey [" << xPos << "][" << yPos << "]\n";
				if (print_console_animation_create) {
					std::this_thread::sleep_for(std::chrono::milliseconds(print_console_animation_pause_ms));
					if (use_VT100_escape_sequence)
						map->clearMapFromConsole();
					else
						sim::clearConsole();
				}
				map->print();
			}
			if (print_file) {
				//Vollstaendige Map in Datei schreiben
				if (print_file_positions_detailed) {
					for (int y = 0; y < mapYSize; y++) {
						for (int x = 0; x < mapXSize; x++) {
							fileStream << steps << " " << map->getEntity(x, y)->getRole() << " " << x << " " << y << " ";
						}
						fileStream << "\n";
					}
				}
				//Position aller Entitys, die nicht null sind, in datei schreiben
				else if (print_file_positions_detailed_compressed) {
					for (int y = 0; y < mapYSize; y++) {
						for (int x = 0; x < mapXSize; x++) {
							if (map->getEntity(x, y)->getRole() != null)
								fileStream << steps << " " << map->getEntity(x, y)->getRole() << " " << x << " " << y << " ";
						}
					}
					fileStream << "\n";
				}
			}
		}
	}

	//Entity Tracker
	void Simulation::clearEntityTracker() {
		for (int i = 0; i < entityTracker.size(); i++) {
			if (entityTracker[i].expired()) {
				entityTracker.erase(entityTracker.begin() + i);
			}
		}
	}
	void Simulation::addToEntityTracker(const int& xPos, const int& yPos) {
		entityTracker.emplace_back(std::weak_ptr<Entity>(map->getEntity(xPos, yPos)));
	}
	void Simulation::updateEntityTracker() {
		entityTracker.clear();
		for (int y = 0; y < mapYSize; y++) {
			for (int x = 0; x < mapXSize; x++) {
				if (map->getEntity(x, y)->getRole() != null)
					addToEntityTracker(x, y);
			}
		}
	}

	//Sonstiges
	int Simulation::getRoleCount(const Role& role) const {
		int counter = 0;
		for (int i = 0; i < entityTracker.size(); i++) {
			if (std::shared_ptr<Entity> tmp_ptr = entityTracker[i].lock())
				if (tmp_ptr->getRole() == role)
					counter++;
		}
		return counter;
	}

	//Ausgabe in Datei oder Konsole abhaengig von den Einstellungen
	void Simulation::printStep() {
		if (print_console) {
			if (print_console_map && !print_console_detailed_map && !print_console_animation_create)
				map->print();
			if (print_console_entity_count && !print_console_animation_create) {
				std::cout << "\nPredator:" << getRoleCount(predator) << "\n";
				std::cout << "Prey    :" << getRoleCount(prey) << "\n";
				std::cout << "Plant   :" << getRoleCount(plant) << "\n\n";
			}
		}
		if (print_file) {
			if (print_file_positions_detailed) {}
			else if (print_file_positions_detailed_compressed) {}
			else if (print_file_entity_count) {
				fileStream << steps << " ";
				fileStream << predator << " " << getRoleCount(predator) << " ";
				fileStream << prey << " " << getRoleCount(prey) << " ";
				fileStream << plant << " " << getRoleCount(plant) << " ";
				fileStream << null << " " << getRoleCount(null) << " ";
				if (!print_file_positions && !print_file_positions_compressed && !print_file_positions_detailed)
					fileStream << "\n";
			}
			if (print_file_positions_detailed) {}
			else if (print_file_positions_detailed_compressed) {}
			else if (print_file_positions_compressed) {
				for (int y = 0; y < mapYSize; y++) {
					for (int x = 0; x < mapXSize; x++) {
						if (map->getEntity(x, y)->getRole() != null)
							fileStream << steps << " " << map->getEntity(x, y)->getRole() << " " << x << " " << y << " ";
					}
				}
				fileStream << "\n";
			}
			else if (print_file_positions) {
				for (int y = 0; y < mapYSize; y++) {
					for (int x = 0; x < mapXSize; x++) {
						fileStream << steps << " " << map->getEntity(x, y)->getRole() << " " << x << " " << y << " ";
					}
					fileStream << "\n";
				}
			}
		}
	}

	//Einstellungen laden
	void Simulation::loadSimulationSettings() {
		loadSimulationSettings("./Settings/simulationSettings.txt");
	}
	//Einstellungen laden
	void Simulation::loadSimulationSettings(const char* fileName) {
		std::ifstream inputFileStream(fileName);
		std::string input;

		if (inputFileStream.is_open()) {
			std::cout << "Lade Einstellungen...\n\n";

			//print_console
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_console;

			//print_console_map
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_console_map;

			//print_console_detailed_map
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_console_detailed_map;

			//print_console_score_map
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_console_score_map;

			//print_console_entity_count
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_console_entity_count;

			//print_console_animation_create
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_console_animation_create;

			//print_console_animation_pause_ms
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_console_animation_pause_ms;

			//print_file_positions
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_file_positions;

			//print_file_positions_compressed
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_file_positions_compressed;

			//print_file_positions_detailed_compressed
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_file_positions_detailed_compressed;

			//print_file_positions_detailed
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_file_positions_detailed;

			//print_file_entity_count
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::print_file_entity_count;

			//predator_max_age
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::predator_max_age;

			//predator_reproduction_threshold
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::predator_reproduction_threshold;

			//predator_reproduction_cost
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::predator_reproduction_cost;

			//predator_quantity
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			if(input != "0")
				std::istringstream(input) >> Simulation::predator_quantity;

			//predator_vision_range
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::predator_vision_range;

			//predator_movement_range
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::predator_movement_range;

			//prey_max_age
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::prey_max_age;

			//prey_reproduction_threshold
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::prey_reproduction_threshold;

			//prey_reproduction_cost
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::prey_reproduction_cost;

			//prey_quantity
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			if(input != "0")
				std::istringstream(input) >> Simulation::prey_quantity;

			//prey_vision_range
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::prey_vision_range;
			std::cout << "Hier ist die prey_vision_range" << Simulation::prey_vision_range << "\n";

			//prey_movement_range
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::prey_movement_range;

			//plant_quantity
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			if(input != "0")
				std::istringstream(input) >> Simulation::plant_quantity;

			//plants_respawn
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::plants_respawn;

			//plant_food_count
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::plant_food_count;

			//use_VT100_escape_sequence
			std::getline(inputFileStream, input);
			std::cout << input << "\n";
			std::getline(inputFileStream, input);
			std::istringstream(input) >> Simulation::use_VT100_escape_sequence;

			inputFileStream.close();
		}
		else {
			std::cout << "Datei \"simulationSettings.txt\" konnte nicht geoeffnet werden\n";
		}
	}
}