//TODO x, y der Map anpassbar machen
//TODO Performance testing of 
#include "Simulation.h"
#include <iomanip>

namespace sim {
	Simulation::Simulation() : mapSize{ 10 } {
		map = new Map(mapSize);
	}
	Simulation::Simulation(int mapSize) : mapSize{ mapSize } {
		map = new Map(mapSize);
	}
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

		map->spawn(Fuchs, mapSize);
		map->spawn(Ente, mapSize);
		map->spawn(Grass, mapSize * 2);

		map->print();
	}

	void Simulation::createTestMap() {
		Predator Fuchs("Fuchs");
		Vision vision("Fuchs vision");
		vision.setRange(2);
		Fuchs.setVision(vision);
		Fuchs.setAttack(Attack());
		Fuchs.setMovement(Movement());

		std::cout << "Movement Range: " << Fuchs.getMovement()->getRange() << std::endl;

		std::cout << "Vision Range: " << Fuchs.getVision()->getRange() << std::endl;

		Prey Ente("Ente");
		Ente.setMovement(Movement());
		Ente.setVision(Vision());

		Plant Grass("Grass");

		map->setEntity(Fuchs, 1, 1);
		map->setEntity(Fuchs, 2, 2);
		std::cout << "Vision aus Map extrahiert: " << map->getEntity(2, 2)->getVision()->getRange() << std::endl;
		std::cout << "Movement aus Map extrahiert: " << map->getEntity(2, 2)->getMovement()->getRange() << std::endl;
		map->setEntity(Fuchs, 8, 8);
		map->setEntity(Fuchs, 9, 9);
		std::cout << "Vision aus Map extrahiert: " << map->getEntity(2, 3)->getVision()->getRange() << std::endl;
		map->setEntity(Ente, 7, 7);
		map->setEntity(Grass, 4, 4);

		map->print();
		moveEntity(8, 8);

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
		int xBuf, yBuf;
			  
		if (role == predator) {
			int vision = map->getEntity(xPos, yPos)->getVision()->getRange();
			int movement = map->getEntity(xPos, yPos)->getMovement()->getRange();
			
			std::cout << "xPos: " << xPos << ", yPos: " << yPos << ", vision: " << vision << std::endl;
			
			//Pruefen, ob Sichtweite die Spielfeldgroesse ueberschreitet
			xMin = xPos - vision < 0 ? 0 : xPos - vision;
			xMax = map->getXSize() - 1 - xPos - vision < 0 ? map->getXSize() - 1 : xPos + vision;
			yMin = yPos - vision < 0 ? 0 : yPos - vision;
			yMax = map->getYSize() - 1 - yPos - vision < 0 ? map->getYSize() - 1 : yPos + vision;

			//Unterscheiden von Faellen am Rande der Map
			xBuf = xPos - xMin < vision ? xPos - xMin : xMax - xPos ? xMax - xPos : 0;
			yBuf = yPos - yMin < vision ? yPos - yMin : yMax - yPos ? yMax - yPos : 0;

			score.resize(xMax - xMin + 1, std::vector<int>(yMax - yMin + 1, 0));

			std::cout << xBuf << ", " << yBuf << std::endl;
			std::cout << xMin << ", " << xMax << ", " << yMin << ", " << yMax << std::endl;

			//Felder im Umkreis durchgehen
			for (int x = 0; x < xMax - xMin + 1; x++) {
				for (int y = 0; y < yMax - yMin + 1; y++) {
					std::cout << "Ueberpruefe bei x=" << x << ", y=" << y << "\n";
					std::cout << "-> Map Pos:     x=" << x + xPos - xBuf << ", y=" << y + yPos - yBuf << "\n";

					if (map->getEntity(x + xPos - xBuf - 1, y + yPos - yBuf - 1)->getRole() == prey)
						score[x][y] += 4;
					else if (map->getEntity(x + xPos - xBuf - 1, y + yPos - yBuf - 1)->getRole() == predator)
						score[x][y] -= 10;

					score[x][y] = x + vision - xMax == 0 && y + vision - yMax == 0 ? 0 : score[x][y];
					//neuen Bestscore setzen
					highscore = score[x][y] > highscore ? score[x][y] : highscore;
				}
			}
			//Aktuelles Feld auf neutral sezten, fuer z.B. den Fall, dass man komplett von Artgenossen umrundet ist
			//score[xMin - xMax][yMin - yMax] = 0;

			std::cout << "Highscore: " << highscore << std::endl;

			for (int x = 0; x < vision + 1; x++) {

			}
		}
		else if (role == prey) {
			//Prey p((*map->getPrey));

		}

		for (int x = 0; x < score.size(); x++) {
			for (int y = 0; y < score[0].size(); y++) {
				std::cout << "+---";
			}
			std::cout << "+\n";
			for (int y = 0; y < score[0].size(); y++) {
				std::cout << "|" << std::setw(3) << score[x][y];
			}
			std::cout << "|\n";
		}
		for (int y = 0; y < score[0].size(); y++) {
			std::cout << "+---";
		}
		std::cout << "+\n";
	}
}