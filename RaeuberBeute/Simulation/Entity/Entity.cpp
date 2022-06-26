//Klasse zum erstellen von Tieren für die Simulation
#include "Entity.h"

namespace sim {
	//Konstruktor
	Entity::Entity() :role{ null }, xPos{ -1 }, yPos{ -1 }{}
	Entity::Entity(const Entity& Entity) :role{ Entity.role }, xPos{ Entity.xPos }, yPos{ Entity.yPos } {}
	Entity::Entity(Role role) : role{ role } {}
	
	//get
	Role Entity::getRole() const { return role; }
	int Entity::getAge() const { return age; }
	int Entity::getXPos() const { return xPos; }
	int Entity::getYPos() const { return yPos; }

	//set
	void Entity::setPos(int xPos, int yPos) {
		this->xPos = xPos;
		this->yPos = yPos;
	}
	void Entity::setXPos(int xPos) {
		this->xPos = xPos; 
	}
	void Entity::setYPos(int yPos) {
		this->yPos = yPos; 
	}

	void Entity::setAge(int age) {
		this->age = age;
	}
}