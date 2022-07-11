#include "Entity.h"

namespace sim {
	//Konstruktor
	Entity::Entity() :role{ null }, xPos{ -1 }, yPos{ -1 }, name{ "Entity" } {}
	Entity::Entity(const Role& role, const std::string& name) : role{ role }, name{ name } {}
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
	void Entity::setPos(const int& xPos, const int& yPos) {
		this->xPos = xPos;
		this->yPos = yPos;
	}
	void Entity::setXPos(const int& xPos) {
		this->xPos = xPos; 
	}
	void Entity::setYPos(const int& yPos) {
		this->yPos = yPos; 
	}
	void Entity::setAge(const int& age) {
		this->age = age;
	}
	void Entity::setFoodCount(const int& foodCount) {
		this->foodCount = foodCount;
	}

	//sonstiges
	void Entity::eat(const int& food) {
		foodCount += food;
	}
	void Entity::eat(const Entity& food) {
		foodCount += food.getFoodCount();
	}
	void Entity::eat(Entity* food) {
		foodCount += food->getFoodCount();
	}
	void Entity::starve() {
		foodCount -= 1;
	}
	void Entity::starve(const int& hunger) {
		foodCount -= hunger;
	}
	void Entity::getOlder() {
		this->age += 1;
	}
	void Entity::getOlder(const int& age) {
		this->age += age;
	}
}