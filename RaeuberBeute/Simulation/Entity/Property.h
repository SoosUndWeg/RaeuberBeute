#pragma once

#include <string>

namespace sim {

	class Property {
	public:
		Property();
		Property(const char*);
		Property(const std::string&);

		std::string getName() const;
	protected:
		const std::string name;
	};
}