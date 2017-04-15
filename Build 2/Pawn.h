#pragma once
#include "City.h"
#include <string>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace std;

class Pawn
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void Pawn::serialize(Archive & ar, const unsigned int version)
	{
		ar & city;
	}

	// City is always a reference because always populated as a reference to another object city.
	City * city;

public:

	Pawn(City * origin);

	// Getters and setters. Here we use references instead of pointers to get used to both techniques.
	City * getCity();
	void setCity(City * city);

	// Here for demonstration purpose.
	void displayInfo();
};

