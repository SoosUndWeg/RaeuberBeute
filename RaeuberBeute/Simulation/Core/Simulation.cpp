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

	void Simulation::moveEntity(int xPos, int yPos) {
		Role role = map->getEntity(xPos, yPos)->getRole();

		if (role == predator) {
			//Predator p((*map->getPredator(xPos, yPos)));

		}
		else if (role == prey) {
			//Prey p((*map->getPrey));

		}
	}
}