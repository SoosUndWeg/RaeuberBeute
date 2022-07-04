#include "Entity.h"
#include <iostream>

namespace sim {
	//Konstruktor
	Entity::Entity() :role{ null }, xPos{ -1 }, yPos{ -1 }, name{ "Entity" } {}
	Entity::Entity(Role role, std::string name) : role{ role }, name{ name } {}
	//Copy Constructor
	Entity::Entity(Entity& entity) : role{ entity.getRole() }, name{ entity.name } {
		this->vision = entity.vision;
		this->movement = entity.movement;
		this->attack = entity.attack;
		this->age = entity.age;
		this->xPos = entity.xPos;
		this->yPos = entity.yPos;
		this->foodCount = entity.foodCount;
	}
	Entity::Entity(const Entity& entity) : role{ entity.getRole() }, name{ entity.name } {
		this->vision = entity.vision;
		this->movement = entity.movement;
		this->attack = entity.attack;
		this->age = entity.age;
		this->xPos = entity.xPos;
		this->yPos = entity.yPos;
		this->foodCount = entity.foodCount;
	}
	Entity::~Entity() {}
	
	//get
	Role Entity::getRole() const { return this->role; }
	int Entity::getAge() const { return this->age; }
	int Entity::getXPos() const { return this->xPos; }
	int Entity::getYPos() const { return this->yPos; }
	std::string Entity::getName() const { return this->name; }
	int Entity::getFoodCount() const { return this->foodCount; }
	
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
	void Entity::setFoodCount(int foodCount) {
		this->foodCount = foodCount;
	}

	//sonstiges
	void Entity::eat(int food) {
		foodCount += food;
	}
	void Entity::eat(Entity food) {
		foodCount += food.getFoodCount();
	}
	void Entity::eat(Entity* food) {
		foodCount += food->getFoodCount();
	}
	void Entity::starve() {
		foodCount -= 1;
	}
	void Entity::starve(int hunger) {
		foodCount -= hunger;
	}
}