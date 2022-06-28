//TODO new entfernen?
#include "EntityLoader.h"

namespace sim {
	EntityLoader::EntityLoader() : entity{ nullptr } {}
	EntityLoader::~EntityLoader() {
		if(entity != nullptr)
			delete entity;
	}

	Entity EntityLoader::load(const char* file) {
		
		std::ifstream fileStream(file);
		std::string bString;
		int bInt;

		if (fileStream.is_open()) {
			try {
				entity = new Entity();

				std::getline(fileStream, bString);
				//entity->setName(bString);

				std::getline(fileStream, bString);
				std::istringstream(bString) >> bInt;
				//entity->setRole(static_cast<Role>(bInt));

				std::getline(fileStream, bString);
				

				//nach Vision Daten suchen und zuweisen#
				/*
				std::getline(fileStream, bString);
				if (bString == "1") {

					std::getline(fileStream, bString);
					Vision vision(bString.c_str());
					std::cout << vision.getName() << std::endl;
				}
				*/
				return (*entity);
			}
			catch(int i) {
				std::cerr << "File\" " << file << "\" is corrupted. Error Code: " << i << "\n";
			}
		}
		else {
			std::cerr << "Unable to open file!\n";
			return Entity();
		}
		
	}
}