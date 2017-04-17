#pragma once
#include "Card.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>


using namespace std;
class Deck
{
protected:
	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar.register_type(static_cast<EventCard *>(NULL));
		ar.register_type(static_cast<CityCard *>(NULL));
		ar.register_type(static_cast<EpidemicCard *>(NULL));
		ar & this->discard;
		ar & this->deck;
	}
	
	vector<Card *> * deck;
	vector<Card *> * discard;

	Card * drawTop();

public:
	Deck();
	~Deck();

	// Add a card to the deck
	void add(Card * card);

	// Destroy the decks if needed
	void clear();

	int getSize();


};

