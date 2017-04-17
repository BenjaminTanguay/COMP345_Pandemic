#pragma once
#include "Card.h"
#include <iostream>
#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;

class EpidemicCard :
	public Card
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Card>(*this);
		ar & description;
	}

	string description;
	string const title = "Epidemic";
	
public:
	EpidemicCard();
	~EpidemicCard();

	string getDescription();
	virtual void read();
	string virtual getTitle();
};

