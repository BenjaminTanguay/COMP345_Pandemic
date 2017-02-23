#pragma once
#include "Action.h"
#include "ReferenceCard.h"
#include "RoleCard.h"
#include "Pawn.h"

class Player {
protected:
	std::string name;
	RoleCard role;
	ReferenceCard card;
	Pawn pawn;
	std::vector<Action> refList;


public:
	Player() {};

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

	void setRefCard(ReferenceCard card) {
		this->card = card;
	}

	void setRole(RoleCard card) {
		this->getRoleCard() = card;
	}

	RoleCard getRoleCard() {
		return this->role;
	}
	Pawn getPawn() {
		return this->pawn;
	}

	//void setRefList(ReferenceCard card);

};