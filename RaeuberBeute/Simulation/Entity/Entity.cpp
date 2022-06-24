//Klasse zum erstellen von Tieren für die Simulation
#include "Animal.h"

namespace sim {
	//Konstruktor
	Animal::Animal(const Animal& _Animal) {
		role = { _Animal.role };
	}
	Animal::Animal(Role _role) : role{ _role } {}
	

	
}