/*

These Classes represent the base Action and other actions that could be performed by a player

alternativaly this could be murged with eventCard

*/
#include "Action.h"

Action::Action(std::string) {
	this->title = title;
}

Action::Action() {};

std::string Action::getTitle() {
	return this->title;
}

std::string Action::getDescription() {
	return this->description;
}

bool Action::costAction(Action& a) { return true; }

/*

---------------------------MOVEMENTS--------------------------------------

*/

DriveFerry::DriveFerry() {
	this->title = "Drive/Ferry";
	this->description = "Move to a city connected by a white line.";
}

DirectFlight::DirectFlight() {
	this->title = "Direct Flight";
	this->description = "Discard a City card to move to the city named on the card.";
}

CharterFlight::CharterFlight() {
	this->title = "Charter Flight";
	this->description = "Discard the City card that matches the city you are in to move to any city.";
}

ShuttleFlight::ShuttleFlight() {
	this->title = "Shuttle Flight";
	this->description = "Move from a city with a research station to any other city that has a research station.";
}

/*

----------------------------------OTHERS------------------------------------

*/

BuildResearchStation::BuildResearchStation() {
	this->title = "Build a Research Station";
	this->description = "Discard the City card that matches the city you are in to place a researchstation there.";
}

TreatDisease::TreatDisease() {
	this->title = "Treat Disease";
	this->description = "Remove 1 disease cube from the city you are in. If this color is cured, removeall cubesof that colorfrom the city.";
}

ShareKnowledge::ShareKnowledge() {
	this->title = "Share Knowledge";
	this->description = "Either: give the card that matches the city you are in to another player, or take that card from another player.The other player must also be in the city with you.";
}

DiscoverCure::DiscoverCure() {
	this->title = "Discover a Cure";
	this->description = "At any research station, discard 5 City cards of the same disease color to cure that disease.";
}