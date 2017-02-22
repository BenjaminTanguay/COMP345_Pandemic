#pragma once
#include "Action.h"
#include "ReferenceCard.h"
#include "RoleCard.h"

class Player {
protected:
	std::string name;
	RoleCard role;
	ReferenceCard card;
	std::vector<Action> refList;


public:
	Player();

	Player(std::string);

	std::string getName() {
		return this->name;
	}

	std::vector<Action> getRefList() {
		return this-> refList;
	}

	ReferenceCard getRefCard() {
		return this->card;
	}

	void setRole(RoleCard role) {
		this->role = role;
	}

	void setRefCard(ReferenceCard card);

	void setRefList(ReferenceCard card);

};