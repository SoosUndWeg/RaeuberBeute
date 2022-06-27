#pragma once

#include <string>
#include "Property.h"

namespace sim {

	enum Role { null, predator, prey, plant };

	class Entity {
	public:
		//Konstruktor
		Entity();
		Entity(Role);

		//get
		Role getRole() const;
		int getAge() const;
		int getXPos() const;
		int getYPos() const;
		std::string getName() const;

		//set
		void setPos(int, int);
		void setXPos(int);
		void setYPos(int);
		void setAge(int);
		void setRole(Role);
		void setName(std::string);

	private:
		Role role;
		std::string name;
		int age = 0;
		int xPos = -1;
		int yPos = -1;
		int foodCount = 4;
	};
}