//Klasse zum erstellen von Tieren für die Simulation
#include "Entity.h"

namespace sim {
	//Konstruktor
	Entity::Entity() :role{ null }, xPos{ -1 }, yPos{ -1 }{}
	Entity::Entity(const Entity& _Entity) {
		role = { _Entity.role };
		xPos = { _Entity.xPos };
		yPos = { _Entity.yPos };
	}
	Entity::Entity(Role _role) : role{ _role } {}
	

	
}