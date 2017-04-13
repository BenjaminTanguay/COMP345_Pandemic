#pragma once
#include "Card.h"
#include "Location.h"
#include <string>
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
	string virtual getTitle();

	bool operator< (CityCard * card) const;
	bool operator> (CityCard * card) const;
};

