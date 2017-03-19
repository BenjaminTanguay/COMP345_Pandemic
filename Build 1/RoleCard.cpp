#include "RoleCard.h"

RoleCard::RoleCard(string) {
	this->name = name;
}

RoleCard::RoleCard() {
	description = new vector<string>;
}

RoleCard::~RoleCard()
{
	delete description;
	description = nullptr;
}




string RoleCard::getName() {
	return this->name;
}

vector<string> * RoleCard::getDescription() {
	return this->description;
}

/*
string RoleCard::getRole() {
	return this->getName() + "\n" + this->getDescription();
}
*/

bool RoleCard::costRole(RoleCard& role) { return true; }

//virtual void doRole();

/*

---------------------------ROlES--------------------------------------
These Classes represent each role a player can have 
some of these roles can pass control to another player, 
---this is why they get their own class
alternatively they could be implemented like the "EventCard" or simply point to an event

*/

ContigencyPlanner::ContigencyPlanner() {
	this->name = "Contigency Planner";
	this->description->push_back("The Contingency Planner may, as an action, take an");
	this->description->push_back("Event card from anywhere in the Player Discard Pile");
	this->description->push_back("and place it on his Role card.Only 1 Event card can be");
	this->description->push_back("Event card from anywhere in the Player Discard Pile");
	this->description->push_back("on his role card at a time.It does not count against his hand limit");
	this->description->push_back("When the Contingency Planner plays the Event card on his role card, ");
	this->description->push_back("remove this Event card from the game (instead of discarding it)");
}

OperationExpert::OperationExpert() {
	this->name = "Operations Expert";
	this->description->push_back("The Operations Expert may, as an action, either:");
	this->description->push_back("• build a research station in his current city");
	this->description->push_back("without discarding(or using) a City card, or ");
	this->description->push_back("• once per turn, move from a research station to any city");
	this->description->push_back("by discarding any City card.");
}

Dispatcher::Dispatcher() {
	this->name = "Dispatcher";
	this->description->push_back("The Dispatcher may, as an action, either:");
	this->description->push_back("• move any pawn, if its owner agrees, to any city");
	this->description->push_back("containing another pawn, or ");
	this->description->push_back("• move another players pawn, if its owner agrees,");
	this->description->push_back("as if it were his own, discarding your own cards.");
}

QuarantineSpecialist::QuarantineSpecialist() {
	this->name = "Quarantine Specialist";
	this->description->push_back("The Quarantine Specialist prevents both outbreaks and");
	this->description->push_back("the placement of disease cubes in the city she is in");
	this->description->push_back("and all cities connected to that city.She does not affect");
	this->description->push_back("cubes placed during setup.");
}

Researcher::Researcher() {
	this->name = "Researcher";
	this->description->push_back("As an action, the Researcher may give any City card from");
	this->description->push_back("her hand to another player in the same city as her, without");
	this->description->push_back("this card having to match her city.The transfer must be");
	this->description->push_back("from her hand to the other players hand, but it can occur");
	this->description->push_back("on either player's turn.");
}

Medic::Medic() {
	this->name = "Medic";
	this->description->push_back("The Medic removes all cubes, not 1, of the same color");
	this->description->push_back("when doing the Treat Disease action.");
	this->description->push_back("If a disease has been cured, he automatically removes");
	this->description->push_back("all cubes of that color from a city, simply by entering it");
	this->description->push_back("or being there.This does not take an action. The Medics automatic removal of cubes can occur on other players'");
	this->description->push_back("turns, if he is moved by the Dispatcher or the Airlift Event");
}

Scientist::Scientist() {
	this->name = "Scientist";
	this->description->push_back("The Scientist needs only 4 (not 5) City cards of");
	this->description->push_back("the same disease color to Discover a Cure for that");
	this->description->push_back("disease.");
}