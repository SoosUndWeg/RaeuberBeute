#pragma once

#include "../Entity.h"
#include "../Properties/Vision.h"
#include "../Properties/Movement.h"

namespace sim {
	class Prey : public Entity {
	public:
		Vision getVision() const;
		Movement getMovement() const;

		void setVision(Vision);
		void setMovement(Movement);
	private:
		Vision vision;
		Movement movement;
	};
}