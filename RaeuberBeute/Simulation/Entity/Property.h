#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace sim {

	class Property {
	public:
		Property();
		Property(const char*);

		const char* getName();
	protected:
		const char* name;
	};

	class Vision : public Property {
	public:
		using Property::Property;

		void setRange(int);
		void setBlockable(bool);

		int getRange();
		bool isBlockable();
	private:
		int range = 1;
		bool blockable = true;
	};

	class Environment : public Property {
	public:
		using Property::Property;

		void blockMovement(bool);
		void blockVision(bool);

		bool isBlockingMovement();
		bool isBlockingVision();
	private:
		bool blockingMovement = false;
		bool blockingVision = false;
	};

	class Movement : public Property {
	public:
		using Property::Property;

		void setRange(int);
		void setBlockable(bool);

		int getRange();
		bool isBlockable();
	private:
		int range = 1;
		bool blockable = true;
	};

	class Attack : public Property {
	public:
		using Property::Property;
		void setRange(int);

		int getRange();
	private:
		int range = 1;
	};
}