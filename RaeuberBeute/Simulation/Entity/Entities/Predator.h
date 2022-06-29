#pragma once

#include "../Entity.h"

namespace sim {
	struct Predator : public Entity {
		Predator();
		Predator(const char*);
		Predator(std::string);

		Vision getVision() const override;
		Movement getMovement() const override;
		Attack getAttack() const override;

		void setVision(Vision) override;
		void setMovement(Movement) override;
		void setAttack(Attack) override;
	private:
		Vision vision;
		Movement movement;
		Attack attack;
	};
}