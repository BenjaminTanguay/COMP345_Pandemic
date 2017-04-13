#pragma once
#include "Subject.h"
#include "Session.h"
#include "Player.h"
#include "City.h"
#include "GameStateVar.h"
#include "PlayMap.h"
#include "ConsoleFormat.h"


class Statistics :
	public Subject
{
private:

	// cardType to allow for more statistics later on. For now, only citycards are used.
	const enum cardType {
		cityCard = 1,
		eventCard = 2
	};
	// Number of printed lines by the statistics method.
	int lines;

	// Returns the number of event card or city card for any region for any player.
	// For now, takes too much space on screen so the method isn't used.
	int getNumberOfCardsInPlayerHand(int playerId, int region, int cardType);
	
	// Returns the hand size of all player in a vector form.
	vector<string> * getHandSize();

	// Returns the number of disease cubes placed on the map.
	int getNumberOfDiseaseOnMap();

	// Returns the number of cards of a specific region or of event cards
	// left in the deck.
	int getNumberOfCardsInDeck(int region, int cardType);

	// Returns teh number of cards of all regions left in the deck as a vector of string.
	// Each region occupies a different spot in the vector.
	vector<string>* getNumberOfPlayerCardsRemainingInDeck();


protected:
	// Returns the number of diseased city. Protected so that
	// decorator can use the value for its own stats.
	int getNumberOfDiseasedCity();


public:
	Statistics();
	~Statistics();

	virtual int getNumberOfLines();

	virtual int getStatistics(int line);
};

