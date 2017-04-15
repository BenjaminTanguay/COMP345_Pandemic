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
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;
//#include "Role.h"
//#include "EventCard.h" or "Action"

class RoleCard {
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void RoleCard::serialize(Archive & ar, const unsigned int version)
	{
		ar & name;
		ar & description;
	}
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
private:
	friend class boost::serialization::access;

public:
	ContigencyPlanner();

};

class OperationExpert : public RoleCard {
private:
	friend class boost::serialization::access;
public:
	OperationExpert();

};

class Dispatcher : public RoleCard {
private:
	friend class boost::serialization::access;
public:
	Dispatcher();

};

class QuarantineSpecialist : public RoleCard {
private:
	friend class boost::serialization::access;
public:
	QuarantineSpecialist();

};

class Researcher : public RoleCard {
private:
	friend class boost::serialization::access;
public:
	Researcher();

};

class Medic : public RoleCard {
private:
	friend class boost::serialization::access;
public:
	Medic();

};

class Scientist : public RoleCard {
private:
	friend class boost::serialization::access;
public:
	Scientist();

};