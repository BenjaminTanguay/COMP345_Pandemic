#pragma once
#include "Card.h"
#include <iostream>
#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

class EpidemicCard :
	public Card
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void EpidemicCard::serialize(Archive & ar, const unsigned int version)
	{
		ar & description;
	}

	string description;
	
public:
	EpidemicCard();
	~EpidemicCard();

	string getDescription();
	string const title = "Epidemic";
	virtual void read();
	string virtual getTitle();
};

