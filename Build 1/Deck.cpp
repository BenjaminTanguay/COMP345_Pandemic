#include "Deck.h"

Card * Deck::drawTop()
{
	// Draw the card at the top of the deck (top = size - 1, bottom = 0)
	Card * drawn = this->deck->at(this->deck->size() - 1);

	// Remove the card drawn from the deck
	this->deck->erase(this->deck->begin() + this->deck->size() - 1);

	return drawn;
}

Deck::Deck()
{
	this->deck = new vector<Card *>;
	this->discard = new vector<Card *>;
}


Deck::~Deck()
{
	delete deck;
	delete discard;
	deck = NULL;
	discard = NULL;
}

void Deck::add(Card * card)
{
	deck->push_back(card);
}

void Deck::clear()
{
	this->deck->clear();
	this->discard->clear();
}

int Deck::getSize()
{
	return this->deck->size();
}

