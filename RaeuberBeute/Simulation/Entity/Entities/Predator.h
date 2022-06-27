#pragma once

#include "../Entity.h"
#include "../Properties/Vision.h"
#include "../Properties/Movement.h"
#include "../Properties/Attack.h"

namespace sim {
	class Predator : public Entity {
	public:
		Vision getVision() const;
		Movement getMovement() const;
		Attack getAttack() const;

		void setVision(Vision);
		void setMovement(Movement);
		void setAttack(Attack);
	private:
		Vision vision;
		Movement movement;
		Attack attack;
	};
}