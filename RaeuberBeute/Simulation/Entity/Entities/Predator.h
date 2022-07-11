#pragma once

#include "../Entity.h"

namespace sim {
	struct Predator : public Entity {
		Predator();
		Predator(const char*);
		Predator(const std::string&);
		~Predator() override;

		std::shared_ptr<Vision> getVision() const override;
		std::shared_ptr<Movement> getMovement() const override;
		std::shared_ptr<Attack> getAttack() const override;

		void setVision(std::shared_ptr<Vision>) override;
		void setVision(const Vision&) override;
		void setMovement(std::shared_ptr<Movement>) override;
		void setMovement(const Movement&) override;
		void setAttack(std::shared_ptr<Attack>) override;
		void setAttack(const Attack&) override;
	};
}