#pragma once
#include "CommandActionCards.h"
#include "Player.h"
#include "Airlift.h"
#include "OneQuietNight.h"
#include "ResilientPopulation.h"
#include "GovernmentGrant.h"
#include "Forecast.h"

class PlayEventCardController
{
private:
	static bool contingency;
	static vector<Card *> * contingencyList;
	static int contingencyCurrent;
	static vector<Card *> * discard;
public:
	
	static void play(CommandActionCards * command, Player * player, Card * card);
	static vector<Card *> * getDiscard();
	static void pickContingency(Card * card);
	static Card * getContingencyCurrent(int current);
	static int getContingencyCurrent();
	static bool getContingency();
	static bool trashDiscard(EventCard * card);

};

