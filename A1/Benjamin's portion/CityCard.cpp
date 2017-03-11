#include "CityCard.h"


CityCard::CityCard (Location * location) : location(location) {};

CityCard::~CityCard()
{
	delete location;
	location = NULL;
}

void CityCard::read()
{
	location->displayInfo();
}

Location * CityCard::getLocation()
{
	return this->location;
}
