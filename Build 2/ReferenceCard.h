/*

This class is more straight forward: much like "Deck"
this only needs to point to a list of rules and does not really need to do anything
this is a generic card given to each player -it is the same for all

*/

#pragma once

#include "Card.h"
#include "Action.h"
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

class ReferenceCard 
	: public Card {

private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void ReferenceCard::serialize(Archive & ar, const unsigned int version)
	{
		ar & name;
		ar & description;
	}



	std::vector<Action *> * list;
	std::vector<Action> copy;



public:
	ReferenceCard();
	~ReferenceCard();

	virtual void read();

	std::vector<Action *> * copyList(std::vector<Action *> * copy);

	std::vector<Action *> * getList();

	void setReferenceList();
	string getTitle();



};