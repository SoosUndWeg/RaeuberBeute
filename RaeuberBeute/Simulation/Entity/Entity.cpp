//Klasse zum erstellen von Tieren für die Simulation
#include "Entity.h"

namespace sim {
	//Konstruktor
	Entity::Entity() :role{ null }, xPos{ -1 }, yPos{ -1 }, name{ "Entity" } {}
	Entity::Entity(Role role, std::string name) : role{ role }, name{ name } {}
	
	//get
	Role Entity::getRole() const { return this->role; }
	int Entity::getAge() const { return this->age; }
	int Entity::getXPos() const { return this->xPos; }
	int Entity::getYPos() const { return this->yPos; }
	std::string Entity::getName() const { return this->name; }
	
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