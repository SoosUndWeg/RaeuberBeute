#pragma once

#include <string>

namespace sim {

	class Property {
	public:
		Property();
		Property(const char*);
		Property(std::string);

		std::string getName() const;
	protected:
		const std::string name;
	};
}