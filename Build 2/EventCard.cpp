#include "EventCard.h"



EventCard::EventCard(int eventId) : eventId(eventId)
{
	switch (eventId) {
	case 1:
		this->title = "Airlift";
		this->description = "Move a pawn (yours or another player's) to any city. You must have a player's permission to move their pawn";
		break;
	case 2:
		this->title = "One Quiet Night";
		this->description = "The next player to begin the infection phase on their turn may skip that phase entirely";
		break;
	case 3:
		this->title = "Resilient Population";
		this->description = "Take a card from the Infection Discard Pile and remove it from the game.";
		break;
	case 4:
		this->title = "Government Grant";
		this->description = "Add a Research Station to any city for free";
		break;
	case 5:
		this->title = "Forecast";
		this->description = "Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile";
		break;
	}
}


EventCard::~EventCard()
{
}

void EventCard::read()
{
	cout << title << endl << description << endl;
}

string EventCard::getTitle()
{
	return this->title;
}

int EventCard::getEventId()
{
	return eventId;
}

bool EventCard::operator<(EventCard * card) const
{
	return title < card->getTitle();
}

bool EventCard::operator>(EventCard * card) const
{
	return title > card->getTitle();
}

bool EventCard::operator>(CityCard * card) const
{
	return true;
}

bool EventCard::operator<(CityCard * card) const
{
	return false;
}
