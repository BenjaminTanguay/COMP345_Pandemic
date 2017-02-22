// Benjamin Tanguay
// 40009113

#pragma once
#include <iostream>
#include <String>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

// This class is used to store the city name and region for cities, infection cards and player cards.
// Defined as an object contained in the 3 classes mentionned above instead of as an abstract parent class so that the data is written only once instead of 3 times to the disk.
class Location
{
public:
	// Constants assigning a value to a region color. The regions are int because it allows for an easier arithmetic comparison.
	static const int BLUE = 1;
	static const int YELLOW = 2;
	static const int BLACK = 3;
	static const int RED = 4;

	// Default constructor should't be used but is here in case.
	Location();

	// Constructor that should be used. Assigns a name and a region number.
	Location(const string name, const int region);

	// Getters and setters
	string getName();
	int getRegion();

	void setName(const string name);
	void setRegion(const int region);
	
	// Here for demo and debug. Gives the state of the object in the console.
	void displayInfo();

private:

	// Here for the serialization process.
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version);

	// Variables
	string name;
	int region;


};

template<class Archive>
inline void Location::serialize(Archive & ar, const unsigned int version)
{
	ar & region;
	ar & name;
}
