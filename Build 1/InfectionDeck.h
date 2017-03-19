#pragma once
#include "CityCard.h"
#include <vector>
#include <algorithm>
#include "Deck.h"
#include "GameStateVar.h"


using namespace std;

class InfectionDeck : public Deck
{
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

