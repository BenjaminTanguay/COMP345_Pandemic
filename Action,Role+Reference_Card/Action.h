/*

These Classes represent the base Action and other actions that could be performed by a player

alternativaly this could be murged with eventCard

*/
#pragma once

#include "Location.h"

#include <string>

class Action {
protected:
	std::string title;
	std::string description;

public:
	Action(std::string);

	Action() {};

	std::string getTitle();

	std::string getDescription();

	virtual bool costAction(Action& a);

	//virtual void doAction();

};

class Movement : public Action {};

class Other : public Action {};

/*

---------------------------MOVEMENTS--------------------------------------

*/

class DriveFerry : public Movement {
public:
	DriveFerry();

};

class DirectFlight : public Movement {
public:
	DirectFlight();

};

class CharterFlight : public Movement {
public:
	CharterFlight();

};

class ShuttleFlight : public Movement {
public:
	ShuttleFlight();

};

/*

----------------------------------OTHERS------------------------------------

*/

class BuildResearchStation : public Other {
public:
	BuildResearchStation();

};

class TreatDisease : public Other {
public:
	TreatDisease();

};

class ShareKnowledge : public Other {
public:
	ShareKnowledge();

};

class DiscoverCure : public Other {
public:
	DiscoverCure();

};