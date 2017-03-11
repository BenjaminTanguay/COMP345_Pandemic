#pragma once
#include "Card.h"
#include <string>
#include <iostream>

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
};

