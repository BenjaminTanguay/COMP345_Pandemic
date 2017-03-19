#include "InfectionDeck.h"




InfectionDeck::InfectionDeck()
{
}

InfectionDeck::~InfectionDeck()
{
}

void InfectionDeck::shuffle()
{
	random_shuffle(deck->begin(), deck->end());
}

Location * InfectionDeck::draw()
{
	// We draw the card from the top of the deck.
	Card * drawn = drawTop();
	
	// Put it at the top of the discard deck (here top = 0, bottom = size - 1)
	// The difference is because we may need to iterate through the discard pile and show the player the cards.
	// It makes more sense if the last actions done come first in the iteration.
	this->discard->insert(this->discard->begin(), drawn);
	
	// Return the name of the card drawn to resolve infection
	return dynamic_cast<CityCard *>(drawn)->getLocation();
}

Location * InfectionDeck::epidemic()
{
	// Take the card at the bottom of the deck (0 is bottom, size - 1 is top)
	Card * bottom = this->deck->at(0);

	// Increase infectionrate
	GameStateVar::getInstance().incrementInfection();

	// Put it in the discard pile
	this->discard->push_back(bottom);

	// Shuffle the discard pile
	random_shuffle(discard->begin(), discard->end());

	// Put the discard pile in the regular deck
	for (unsigned i = 0; i < discard->size(); ++i) {
		deck->push_back(discard->at(i));
	}

	// Reset the discard pile (since cards are now in the deck)
	discard->clear();

	// Return the card drawn at the bottom of the deck to resolve infection
	return dynamic_cast<CityCard *>(bottom)->getLocation();
}

vector<CityCard*>* InfectionDeck::drawForeCast()
{
	vector<CityCard *> * foreCast = new vector<CityCard *>;
	for (unsigned i = 0; i < 6; ++i) {
		foreCast->push_back(dynamic_cast<CityCard *>(drawTop()));
	}
	return foreCast;
}

void InfectionDeck::putForeCast(vector<CityCard*> * top)
{
	for (unsigned i = 0; i < 6; ++i) {
		deck->push_back(top->at(top->size() - 1));
		top->erase(top->begin() + top->size() - 1);
	}
	delete top;
	top = NULL;
}

vector<Card *> * InfectionDeck::getDiscard()
{
	return this->discard;
}
