#pragma once

namespace sim {

	enum Role { predator, prey };

	class Animal {
	public:
		//Konstruktor
		Animal();
		Animal(Role _role);

		Role getRole() const { return role; }
		int getAge() const { return age; }
		int getXPos() const { return xPos; }
		int getYPos() const { return yPos; }

	protected:
		Role role;
		int age = 0;
		int xPos;
		int yPos;
	};

	//Vererbte Klasse Predator von Animal
	class Predator : public Animal {
		//Predator(Role _role);
	};

	//Vererbte Klasse Prey von Animal
	class Prey : public Animal {

	};
}