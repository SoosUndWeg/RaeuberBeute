#include "Entity.h"
#include <iostream>

namespace sim {
	//Konstruktor
	Entity::Entity() :role{ null }, xPos{ -1 }, yPos{ -1 }, name{ "Entity" } {}
	Entity::Entity(Role role, std::string name) : role{ role }, name{ name } {}
	//Copy Constructor
	Entity::Entity(Entity& entity) : role{ entity.getRole() } {
		this->vision = entity.vision;
		this->movement = entity.movement;
		this->attack = entity.attack;
		this->age = entity.age;
		this->xPos = entity.xPos;
		this->yPos = entity.yPos;
		this->foodCount = entity.foodCount;
	}
	Entity::~Entity() {
		std::cout << "Entity wird geloescht\n";
	}
	
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