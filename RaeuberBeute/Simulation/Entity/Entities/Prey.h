#pragma once

#include "../Entity.h"

namespace sim {
	struct Prey : public Entity {
		Prey();
		Prey(const char*);
		Prey(std::string);

		Vision getVision() const override;
		Movement getMovement() const override;

		void setVision(Vision) override;
		void setMovement(Movement) override;
	private:
		Vision vision;
		Movement movement;
	};
}