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
					//score[x][y] = 
				}
			}
		}
		else if (role == prey) {
			//Prey p((*map->getPrey));

		}
	}
}