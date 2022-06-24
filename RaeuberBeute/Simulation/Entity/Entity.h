#pragma once

namespace sim {

	enum Role { predator, prey, plant, null };

	class Entity {
	public:
		//Konstruktor
		Entity();
		Entity(const Entity&);
		Entity(Role);

		//get
		Role getRole() const;
		int getAge() const;
		int getXPos() const;
		int getYPos() const;

		//set
		void setPos(int, int);
		void setXPos(int _xPos);
		void setYPos(int _yPos);
		
		void setAge(int _age);

	private:
		Role role;
		int age = 0;
		int xPos = -1;
		int yPos = -1;
	};
}