#pragma once
#include "CommandActionCards.h"
#include "Session.h"

class ResilientPopulation :
	public CommandActionCards
{
private:
	CityCard * card;
public:
	ResilientPopulation(CityCard * card);
	~ResilientPopulation();

	void execute();
};

