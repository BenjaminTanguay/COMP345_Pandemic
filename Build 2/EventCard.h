#pragma once
#include "Card.h"
#include <string>
#include <iostream>
#include "CityCard.h"

using namespace std;

class EventCard :
	public Card
{
private:
	int eventId;
	string title;
	string description;
public:
	EventCard(int eventId);
	~EventCard();

	virtual void read();

	string getTitle();
	int getEventId();
	bool operator<(EventCard * card) const;
	bool operator>(EventCard * card) const;
	bool operator>(CityCard * card) const;
	bool operator<(CityCard * card) const;
};

