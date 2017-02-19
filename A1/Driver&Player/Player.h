#pragma once

#include "Action.h"
#include "ReferenceCard.h"
#include "RoleCard.h"

class Player {
protected:
	std::string name;
	std::string description;

public:
	

	Player() {};

	std::string getName() {
		return this->name;
	}

	std::string getDescription() {
		return this->description;
	}
};