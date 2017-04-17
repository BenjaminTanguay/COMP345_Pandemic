#pragma once
#include "Card.h"
#include <string>
#include <iostream>
#include "CityCard.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;

class EventCard :
	public Card
{
private:

	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Card>(*this);
		ar & eventId;
		ar & title;
		ar & description;
	}

	int eventId;
	string title;
	string description;
public:
	EventCard(int eventId);
	EventCard();
	~EventCard();

	virtual void read();

	string getTitle();
	int getEventId();
	bool operator<(EventCard * card) const;
	bool operator>(EventCard * card) const;
	bool operator>(CityCard * card) const;
	bool operator<(CityCard * card) const;
};

