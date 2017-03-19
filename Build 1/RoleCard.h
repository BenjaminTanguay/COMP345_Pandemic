/*

These Classes represent the base role of players 
andf each role a player can have
some of these roles can pass control to another player,
---this is why they get their own class so that they can be given more "importance"

alternatively they could be implemented like the "EventCard" or simply point to an event

*/
#pragma once

#include <string>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//#include "Role.h"
//#include "EventCard.h" or "Action"

class RoleCard {
protected:
	string name;
	vector<string> * description;

public:

	RoleCard(string);

	RoleCard();
	~RoleCard();

	string getName();

	vector<string> * getDescription();

	/*
	string getRole() {
		return this->getName() + "\n" + this->getDescription();
	}
	*/

	virtual bool costRole(RoleCard& role);

	//virtual void doRole();

};

/*

---------------------------ROlES--------------------------------------

*/

class ContigencyPlanner : public RoleCard {
public:
	ContigencyPlanner();

};

class OperationExpert : public RoleCard {
public:
	OperationExpert();

};

class Dispatcher : public RoleCard {
public:
	Dispatcher();

};

class QuarantineSpecialist : public RoleCard {
public:
	QuarantineSpecialist();

};

class Researcher : public RoleCard {
public:
	Researcher();

};

class Medic : public RoleCard {
public:
	Medic();

};

class Scientist : public RoleCard {
public:
	Scientist();

};