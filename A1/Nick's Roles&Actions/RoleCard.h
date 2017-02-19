#pragma once

#include <string>
#include <iostream>

#include "Role.h"
//#include "EventCard.h"

class RoleCard {
	protected:
		std::string name;
		std::string description;
		Action role;

	public:
		bool costRole() {}

		void doRole() {}

		RoleCard(std::string) {
			this->name = name;
		}

		RoleCard() {};

		std::string getname() {
			return this->name;
		}

		std::string getDescription() {
			return this->description;
		}

		std::string getRole() {
			return this->role.getTitle() + "\n" + this->role.getDescription();
		}



};

class ContigencyPlanner : public RoleCard {
	public:
		ContigencyPlanner() {
			this->name = "Contigency Planner";
			this->description = "The Contingency Planner may, as an action, take an\n"
				"Event card from anywhere in the Player Discard Pile\n"
				"and place it on his Role card.Only 1 Event card can be\n"
				"on his role card at a time.It does not count against his\n"
				"hand limit.\n"
				"When the Contingency Planner plays the Event card on his role card,\n"
				"remove this Event card from the game(instead of discarding i";
		}

};

class OperationExpert : public RoleCard {
public:
	OperationExpert() {
		this->name = "Operations Expert";
		this->description = "The Operations Expert may, as an action, either:\n"
			"• build a research station in his current city\n"
			"without discarding(or using) a City card, or \n"
			"• once per turn, move from a research station to any city\n"
			"by discarding any City card.";
	}

};

class Dispatcher : public RoleCard {
public:
	Dispatcher() {
		this->name = "Dispatcher";
		this->description = "The Dispatcher may, as an action, either:\n"
			"• move any pawn, if its owner agrees, to any city\n"
			"containing another pawn, or \n"
			"• move another player’s pawn, if its owner agrees,\n"
			"as if it were his own, discarding your own cards.";
	}

};

class QuarantineSpecialist : public RoleCard {
public:
	QuarantineSpecialist() {
		this->name = "Quarantine Specialist";
		this->description = "The Quarantine Specialist prevents both outbreaks and\n"
			"the placement of disease cubes in the city she is in\n"
			"and all cities connected to that city.She does not affect\n"
			"cubes placed during setup.";
	}

};

class Researcher : public RoleCard {
public:
	Researcher() {
		this->name = "Researcher";
		this->description = "As an action, the Researcher may give any City card from\n"
			"her hand to another player in the same city as her, without\n"
			"this card having to match her city.The transfer must be\n"
			"from her hand to the other player’s hand, but it can occur\n"
			"on either player’s turn.";
	}

};

class Medic : public RoleCard {
public:
	Medic() {
		this->name = "Medic";
		this->description = "The Medic removes all cubes, not 1, of the same color\n"
			"when doing the Treat Disease action.\n"
			"If a disease has been cured, he automatically removes\n"
			"all cubes of that color from a city, simply by entering it\n"
			"or being there.This does not take an action. The Medic’s automatic removal of cubes can occur on other players’\n"
			"turns, if he is moved by the Dispatcher or the Airlift Event";
	}

};

class Scientist : public RoleCard {
public:
	Scientist() {
		this->name = "Scientist";
		this->description = "he Scientist needs only 4 (not 5) City cards of\n"
			"the same disease color to Discover a Cure for that\n"
			"disease.";
	}

};