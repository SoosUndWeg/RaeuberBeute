#pragma once

namespace sim {

	enum Role { predator, prey };

	class Animal {
	public:
		//Konstruktor
		Animal(const Animal&);
		Animal(Role);

		Role getRole() const { return role; }
		int getAge() const { return age; }
		int getXPos() const { return xPos; }
		int getYPos() const { return yPos; }

	private:
		Role role;
		int age = 0;
		int xPos = 0;
		int yPos = 0;
	};
}