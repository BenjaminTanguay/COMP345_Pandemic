#pragma once
#include "CommandActionCards.h"
#include <vector>
#include "InfectionDeck.h"
#include "Session.h"

class Forecast :
	public CommandActionCards
{
private:
	vector<CityCard *> * forecast;

public:
	Forecast(vector<CityCard *> * forecast);
	~Forecast();

	void execute();
};

