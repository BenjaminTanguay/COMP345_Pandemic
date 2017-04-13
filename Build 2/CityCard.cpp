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

string CityCard::getTitle()
{
	return location->getName();
}

bool CityCard::operator<(CityCard * card) const
{
	return this->location < card->getLocation();
}

bool CityCard::operator>(CityCard * card) const
{
	return this->location > card->getLocation();
}


