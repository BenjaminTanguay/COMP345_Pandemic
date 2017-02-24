#pragma once
#include "Card.h"
#include "EventCard.h"
#include "EpidemicCard.h"
#include "CityCard.h"
#include "Deck.h"
#include <algorithm>

using namespace std;

class PlayerDeck : public Deck
{


public:
	PlayerDeck();
	~PlayerDeck();

	Card * draw();
	void toDiscard(Card * card);
	void initialize();

	void shuffleEpidemic(int i);
};

