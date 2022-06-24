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
	
	//get
	Role Entity::getRole() const { return role; }
	int Entity::getAge() const { return age; }
	int Entity::getXPos() const { return xPos; }
	int Entity::getYPos() const { return yPos; }

	//set
	void Entity::setPos(int _xPos, int _yPos) {
		xPos = _xPos;
		yPos = _yPos;
	}
	void Entity::setXPos(int _xPos) {
		xPos = _xPos; 
	}
	void Entity::setYPos(int _yPos) {
		yPos = _yPos; 
	}

	void Entity::setAge(int _age) {
		age = _age;
	}
}