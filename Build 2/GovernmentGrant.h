#pragma once
#include "CommandActionCards.h"
#include "City.h"

class GovernmentGrant :
	public CommandActionCards
{
private:
	City * city;
public:
	GovernmentGrant(City * city);
	~GovernmentGrant();

	void execute();
};

