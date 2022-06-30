//TODO x, y der Map anpassbar machen
#include "Simulation.h"

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
		//std::unique_ptr<Entity> Fuchs = std::make_unique<Predator>("Fuchs");
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
		Fuchs.setVision(Vision());
		Fuchs.setAttack(Attack());
		Fuchs.setMovement(Movement());

		Prey Ente("Ente");
		Ente.setMovement(Movement());
		Ente.setVision(Vision());

		Plant Grass("Grass");

		map->setEntity(Fuchs, 2, 2);
		map->setEntity(Ente, 3, 3);
		map->setEntity(Grass, 4, 4);

		map->print();
		moveEntity(2, 2);
	}

	//Logik der Entscheidung
	//Suche Felder in Sichtweite ab und bewerte, wie gut sie sind
	void Simulation::moveEntity(int xPos, int yPos) {
		Role role = map->getEntity(xPos, yPos)->getRole();
		std::vector<std::vector<int>> score;

		if (role == predator) {
			int vision = map->getEntity(1, 2)->getVision().getRange();
			score.resize(vision, std::vector<int>(vision, 0));

			//Felder im Umkreis durchgehen
			for (int x = 0; x < vision + 1; x++) {
				for (int y = 0; y < vision + 1; y++) {
					//score[x][y] +=
					if (map->getEntity(x, y)->getRole() == prey)
						score[x][y] += 4;
					else if (map->getEntity(x, y)->getRole() == predator)
						score[x][y] -= 10;

				}
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
				std::cout << "| " << score[x][y] << " ";
			}
			std::cout << "|\n";
			for (int y = 0; y < score[0].size(); y++) {
				std::cout << "+---";
			}
			std::cout << "+\n";
		}
	}
}