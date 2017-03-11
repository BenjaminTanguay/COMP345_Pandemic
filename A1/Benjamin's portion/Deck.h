#pragma once
#include "Card.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
class Deck
{
protected:
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
};

