#pragma once
#include "Card.h"
#include "EventCard.h"
#include "EpidemicCard.h"
#include "CityCard.h"
#include "Deck.h"
#include <algorithm>
#include <random>
#include "Session.h"


using namespace std;

class PlayerDeck : public Deck
{
private:
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

