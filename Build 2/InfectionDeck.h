#pragma once
#include "CityCard.h"
#include <vector>
#include <algorithm>
#include "Deck.h"
#include "GameStateVar.h"
#include <random>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>


using namespace std;

class InfectionDeck : public Deck
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Deck>(*this);
		ar & this->discard;
		ar & this->deck;
	}

public:
	InfectionDeck();
	~InfectionDeck();

	// Shuffle the deck once it is constructed
	void shuffle();

	// Used to do a regular draw from the deck
	Location * draw();
	// Used to handle an epidemic card's effect
	Location * epidemic();

	// Methods used to handle the Forecast event card
	vector<CityCard *> * drawForeCast();
	// NOTE: The card at top[0] will be the one to be put first in the deck
	void putForeCast(vector<CityCard *> * top);

	// Return the discard pile to handle the Resilient Population special event
	vector<Card *> * getDiscard();
};

