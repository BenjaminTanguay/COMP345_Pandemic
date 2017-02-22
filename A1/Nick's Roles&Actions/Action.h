#pragma once

#include <string>

class Action {
	protected:
		std::string title;
		std::string description;

	public:
		Action(std::string) {
			this->title = title;
		}

		Action();

		std::string getTitle() {
			return this->title;
		}

		std::string getDescription() {
			return this->description;
		}

		virtual bool costAction(Action& a);

		virtual void doAction();
		
};

class Movement : public Action {};

class Other : public Action {};

/*

---------------------------MOVEMENTS--------------------------------------

*/

class DriveFerry : public Movement {
	public:
		DriveFerry() {
		this->title = "Drive/Ferry";
		this->description = "Move to a city connected by a white line.";
		}
		
};

class DirectFlight : public Movement {
	public:
		DirectFlight() {
			this->title = "Direct Flight";
			this->description = "Discard a City card to move to the city named on the card.";
		}

};

class CharterFlight : public Movement {
	public:
		CharterFlight() {
			this->title = "Charter Flight";
			this->description = "Discard the City card that matches the city you are in to move to any city.";
		}

};

class ShuttleFlight : public Movement {
	public:
		ShuttleFlight() {
			this->title = "Shuttle Flight";
			this->description = "Move from a city with a research station to any other city that has a research station.";
		}

};

/*

----------------------------------OTHERS------------------------------------

*/

class BuildResearchStation : public Other {
public:
	BuildResearchStation() {
		this->title = "Build a Research Station";
		this->description = "Discard the City card that matches the city you are in to place a researchstation there.";
	}

};

class TreatDisease : public Other {
public:
	TreatDisease() {
		this->title = "Treat Disease";
		this->description = "Remove 1 disease cube from the city you are in. If this color is cured, removeall cubesof that colorfrom the city.";
	}

};

class ShareKnowledge : public Other {
public:
	ShareKnowledge() {
		this->title = "Share Knowledge";
		this->description = "Either: give the card that matches the city you are in to another player, or take that card from another player.The other player must also be in the city with you.";
	}

};

class DiscoverCure : public Other {
public:
	DiscoverCure() {
		this->title = "Discover a Cure";
		this->description = "At any research station, discard 5 City cards of the same disease color to cure that disease.";
	}

};