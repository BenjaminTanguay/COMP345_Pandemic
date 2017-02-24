#pragma once
#include "Card.h"
#include "Location.h"
class CityCard :
	public Card
{
private:
	Location * location;

public:
	CityCard(Location * location);
	~CityCard();

	virtual void read();
	Location * getLocation();
};

