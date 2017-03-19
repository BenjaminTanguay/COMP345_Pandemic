/*

This class is more straight forward: much like "Deck"
this only needs to point to a list of rules and does not really need to do anything
this is a generic card given to each player -it is the same for all

*/

#include "ReferenceCard.h"

ReferenceCard::ReferenceCard() {
	this->list = new vector<Action *>;
	setReferenceList();

}

ReferenceCard::~ReferenceCard() {
	delete list;
	list = NULL;

}

std::vector<Action *> * ReferenceCard::copyList(std::vector<Action *> * copy) {
	if (this->list->size() < 1)
		std::cout << "No Actions..." << std::endl;

	else
		for (auto it : *(this->list)) {
			//Action action = *it;
			copy->push_back(it);
		}
	return copy;
}

std::vector<Action *> * ReferenceCard::getList() {
	return this->list;
}

void ReferenceCard::read() {
	if (this->list->size() < 1)
		std::cout << "No Actions..." << std::endl;

	else
		for (auto it : *(this->list)) {
			//Action action = it;
			std::cout << it->getTitle() << it->getDescription() << std::endl;
		}

}

void ReferenceCard::setReferenceList() {
	this->list->push_back(new DriveFerry());
	this->list->push_back(new DirectFlight());
	this->list->push_back(new CharterFlight());
	this->list->push_back(new ShuttleFlight());
	this->list->push_back(new BuildResearchStation());
	this->list->push_back(new TreatDisease());
	this->list->push_back(new ShareKnowledge());
	this->list->push_back(new DiscoverCure());
}

string ReferenceCard::getTitle()
{
	return "Reference card";
}
