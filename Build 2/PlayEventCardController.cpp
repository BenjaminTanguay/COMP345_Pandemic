#include "PlayEventCardController.h"

bool PlayEventCardController::contingency = false;
vector<Card *> * PlayEventCardController::contingencyList = new vector<Card *>;
int PlayEventCardController::contingencyCurrent = 0;
vector<Card *> * PlayEventCardController::discard = new vector<Card *>;



void PlayEventCardController::play(CommandActionCards * command, Player * player, Card * card)
{
	player->discardCard(card);
	discard->push_back(card);
	command->execute();
}

vector<Card *> * PlayEventCardController::getDiscard()
{
	return discard;
}

void PlayEventCardController::pickContingency(Card * card)
{

	PlayEventCardController::contingencyList->push_back(card);
	PlayEventCardController::contingencyCurrent += 1;
	PlayEventCardController::contingency = true;
}

Card * PlayEventCardController::getContingencyCurrent(int  current) {
	return PlayEventCardController::contingencyList->at(current);
}

int  PlayEventCardController::getContingencyCurrent() {
	return PlayEventCardController::contingencyCurrent;
}

bool  PlayEventCardController::getContingency() {
	return PlayEventCardController::contingency;
}

bool PlayEventCardController::trashDiscard(EventCard * card) {
	if(PlayEventCardController::contingencyList->size() >= 1)
		PlayEventCardController::getDiscard()->erase(std::remove(PlayEventCardController::getDiscard()->begin(), PlayEventCardController::getDiscard()->end(), card), PlayEventCardController::getDiscard()->end());
	return false;
}

