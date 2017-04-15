#pragma once
#include "Card.h"
#include "EventCard.h"
#include "EpidemicCard.h"
#include "CityCard.h"
#include "Deck.h"
#include <algorithm>
#include <random>
#include "Session.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>


using namespace std;

class PlayerDeck : public Deck
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & this->discard;
		ar & this->deck;
		ar & blueRegionCards;
		ar & yellowRegionCards;
		ar & blackRegionCards;
		ar & redRegionCards;
		ar & eventCards;
	}

	int blueRegionCards;
	int yellowRegionCards;
	int blackRegionCards;
	int redRegionCards;
	int eventCards;


public:
	PlayerDeck();
	~PlayerDeck();

	Card * draw();
	void toDiscard(Card * card);
	void initialize();

	void shuffleEpidemic(int i);

	int getEventCards();
	void decrementEventCards();
	
	int getSize();
	void incrementRegionCards(int region);
	int getRegionCard(int region);
};

