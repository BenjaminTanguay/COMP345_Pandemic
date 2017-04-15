#pragma once
#include "Card.h"
#include "Location.h"
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
class CityCard :
	public Card
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & location;
	}


	Location * location;

public:
	CityCard(Location * location);
	CityCard();
	~CityCard();

	virtual void read();
	Location * getLocation();
	string virtual getTitle();

	bool operator< (CityCard * card) const;
	bool operator> (CityCard * card) const;
};

