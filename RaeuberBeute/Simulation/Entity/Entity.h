#pragma once

#include <string>
#include "Property.h"
#include "Properties/Vision.h"
#include "Properties/Movement.h"
#include "Properties/Attack.h"

namespace sim {

	enum Role { null, predator, prey, plant };

	class Entity {
	public:
		//Konstruktor
		Entity();
		Entity(Role, std::string);

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

		//Virtual Functions
		virtual Vision getVision() const { return nullptr; }
		virtual Movement getMovement() const { return nullptr; }
		virtual Attack getAttack() const { return nullptr; }

		virtual void setVision(Vision) {};
		virtual void setMovement(Movement) {}
		virtual void setAttack(Attack) {}

	protected:
		const Role role;
		const std::string name;
		
		int age = 0;

		int xPos = -1;
		int yPos = -1;

		int foodCount = 4;
		//static const int foodValue;
	};
}