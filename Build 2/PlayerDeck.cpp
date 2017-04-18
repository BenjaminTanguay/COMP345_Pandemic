#include "PlayerDeck.h"



PlayerDeck::PlayerDeck()
{
	blueRegionCards = 0;
	yellowRegionCards = 0;
	blackRegionCards = 0;
	redRegionCards = 0;
	eventCards = 5;
}


PlayerDeck::~PlayerDeck()
{
}

// We return NULL if there are no more cards, which is a lose condition for the game.
Card* PlayerDeck::draw()
{
	if (this->deck->size() > 0) {
		return this->drawTop();
	}
	return NULL;
}

vector<Card *> * PlayerDeck::getDiscard() {
	return this->discard;
}

void PlayerDeck::toDiscard(Card * card)
{
	this->discard->push_back(card);
}
// Adding the event cards before shuffling. This step is needed before cards are distributed to the players.
// This needs to happen before we add the epidemic cards in the deck.
void PlayerDeck::initialize()
{
	EventCard * eventCard;
	for (unsigned i = 1; i < 6; ++i) {
		eventCard = new EventCard(i);
		this->add(eventCard);
		Session::getInstance()->addEventCards(eventCard);
	}

	std::mt19937 randomSeed{ std::random_device{}() };
	std::shuffle(this->deck->begin(), this->deck->end(), randomSeed);
}

// This method divides the deck in numberOfEpidemicCards portions, then add an epidemic card to each portion, shuffle them individually and add them together.
void PlayerDeck::shuffleEpidemic(int numberOfEpidemicCards)
{
	// We want to know the base number of cards in each divisions.
	int division = this->deck->size() / numberOfEpidemicCards;

	// Here we want to know how many divisions will have 1 more card. Ex: if we have 3.33333 cards in our split decks and 3 decks, then we could have a deck
	// of 4 cards and two decks of 3.
	double decimals = ((this->deck->size() / numberOfEpidemicCards) - division)*numberOfEpidemicCards;
	vector<int> separate;
	// We create a vector and add the number of cards in each split deck portions.
	for (int i = 0; i < numberOfEpidemicCards; ++i) {
		separate.push_back(division + 1);
		if (decimals > 0) {
			separate.at(separate.size() - 1) += 1;
		}
	}
	// We shuffle that vector so that the beginning or the end doesn't always have more cards.
	std::mt19937 randomSeed{ std::random_device{}() };
	shuffle(separate.begin(), separate.end(), randomSeed);
	int lastLoop = 0;

	// Here we use the information above to know where to insert the epidemic cards in the deck and 
	// where to divide the deck to shuffle each separate portions.
	for (int i = 0; i < numberOfEpidemicCards; ++i) {
		this->deck->insert(this->deck->begin() + lastLoop, new EpidemicCard());
		std::mt19937 randomSeed{ std::random_device{}() };
		if (i == numberOfEpidemicCards - 1) {
			shuffle(this->deck->begin() + lastLoop, this->deck->end(), randomSeed);
		}
		else {
			shuffle(this->deck->begin() + lastLoop, this->deck->begin() + lastLoop + separate.at(i) + 1, randomSeed);
		}
		
		lastLoop += separate.at(i);
	}
}

int PlayerDeck::getEventCards()
{
	return eventCards;
}

void PlayerDeck::decrementEventCards()
{
	--eventCards;
}

int PlayerDeck::getSize()
{
	return this->deck->size();
}

void PlayerDeck::incrementRegionCards(int region)
{
	switch (region) {
	case 1:
		++blueRegionCards;
		break;
	case 2:
		++yellowRegionCards;
		break;
	case 3:
		++blackRegionCards;
		break;
	case 4:
		++redRegionCards;
		break;
	default:
		break;
	}
}

int PlayerDeck::getRegionCard(int region)
{
	switch (region) {
	case 1:
		return blueRegionCards;
	case 2:
		return yellowRegionCards;
	case 3:
		return blackRegionCards;
	case 4:
		return redRegionCards;
	default:
		return 0;
	}
}
