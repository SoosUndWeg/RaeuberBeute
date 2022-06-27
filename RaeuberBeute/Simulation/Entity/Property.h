#pragma once

namespace sim {

	class Property {
	public:
		Property();
		Property(const char*);

		const char* getName();
	protected:
		const char* name;
	};
}