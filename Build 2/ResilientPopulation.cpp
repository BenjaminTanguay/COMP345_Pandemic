#include "ResilientPopulation.h"



ResilientPopulation::ResilientPopulation(CityCard * card):card(card)
{
}

ResilientPopulation::~ResilientPopulation()
{
}

void ResilientPopulation::execute()
{
	vector<Card *> * vec = Session::getInstance()->getInfectionDeck()->getDiscard();
	unsigned playerPosition = distance(vec->begin(), find(vec->begin(), vec->end(), card));
	vec->erase(vec->begin() + playerPosition);
	vec = nullptr;
}
