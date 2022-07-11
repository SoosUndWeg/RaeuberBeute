#pragma once

#include <string>
#include <memory>

#include "Properties/Vision.h"
#include "Properties/Movement.h"
#include "Properties/Attack.h"

namespace sim {

	enum Role { null, predator, prey, plant };

	struct Entity {
		//Konstruktor
		Entity();
		Entity(const Role&, const std::string&);
		Entity(Entity&);
		Entity(const Entity&);
		virtual ~Entity();

		//get
		Role getRole() const;
		int getAge() const;
		int getXPos() const;
		int getYPos() const;
		std::string getName() const;
		int getFoodCount() const;

		//set
		void setPos(const int&, const int&);
		void setXPos(const int&);
		void setYPos(const int&);
		void setAge(const int&);
		void setFoodCount(const int&);

		//sonstiges
		void eat(const int&);
		void eat(const Entity&);
		void eat(Entity*);
		void starve();
		void starve(const int&);
		void getOlder();
		void getOlder(const int&);

		//Virtual Functions
		virtual std::shared_ptr<Vision> getVision() const { return vision; }
		virtual std::shared_ptr<Movement> getMovement() const { return movement; }
		virtual std::shared_ptr<Attack> getAttack() const { return attack; }

		virtual void setVision(std::shared_ptr<Vision>) {}
		virtual void setVision(const Vision&) {}
		virtual void setMovement(std::shared_ptr<Movement>) {}
		virtual void setMovement(const Movement&) {}
		virtual void setAttack(std::shared_ptr<Attack>) {}
		virtual void setAttack(const Attack&) {}

	protected:
		const Role role;
		const std::string name;

		std::shared_ptr<Vision> vision = std::make_shared<Vision>();
		std::shared_ptr<Movement> movement = std::make_shared<Movement>();
		std::shared_ptr<Attack> attack = std::make_shared<Attack>();
		
		unsigned int age = 0;

		int xPos = -1;
		int yPos = -1;

		int foodCount = 4;
	};
}