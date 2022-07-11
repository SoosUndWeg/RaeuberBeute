#pragma once

#include "../Entity.h"

namespace sim {
	struct Prey : public Entity {
		Prey();
		Prey(const char*);
		Prey(const std::string&);
		~Prey() override;

		std::shared_ptr<Vision> getVision() const override;
		std::shared_ptr<Movement> getMovement() const override;

		void setVision(std::shared_ptr<Vision>) override;
		void setVision(const Vision&) override;
		void setMovement(std::shared_ptr<Movement>) override;
		void setMovement(const Movement&) override;
	};
}