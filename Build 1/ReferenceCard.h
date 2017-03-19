/*

This class is more straight forward: much like "Deck"
this only needs to point to a list of rules and does not really need to do anything
this is a generic card given to each player -it is the same for all

*/

#pragma once

#include "Card.h"
#include "Action.h"

#include <vector>

class ReferenceCard 
	: public Card {

private:
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