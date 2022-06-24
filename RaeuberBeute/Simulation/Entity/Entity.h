#pragma once

namespace sim {

	enum Role { predator, prey, null };

	class Entity {
	public:
		//Konstruktor
		Entity();
		Entity(const Entity&);
		Entity(Role);

		Role getRole() const { return role; }
		int getAge() const { return age; }
		int getXPos() const { return xPos; }
		int getYPos() const { return yPos; }

		void setXPos(int _xPos) { xPos = { _xPos }; }
		void setYPos(int _yPos) { yPos = { _yPos }; }

	private:
		Role role;
		int age = 0;
		int xPos = -1;
		int yPos = -1;
	};
}