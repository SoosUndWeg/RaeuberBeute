#pragma once

#include "../Entity.h"
#include "../Properties/Vision.h"
#include "../Properties/Movement.h"

namespace sim {
	struct Prey : public Entity {
		Prey();
		Prey(const char*);
		Prey(std::string);

		Vision getVision() const;
		Movement getMovement() const;

		void setVision(Vision);
		void setMovement(Movement);
	private:
		Vision vision;
		Movement movement;
	};
}