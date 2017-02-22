// Benjamin Tanguay
// 40009113

#pragma once
#include "Location.h"
#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;
class City
{
private:

	// Here to allow for serialization of the play map
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version);

	// A static list of all the cities that have a research center --> allows for easier connections of newly established research centers
	// Vector used because it's easy and the only thing we do with this structure is iterate through it. Insertions should be limited to 6 per game.
	static vector<City *> * researchCities;

	// Where the city is and what is its region
	Location * location;

	// Points to other cities connected to this one. Unordered_map for O(1) operations on query.
	unordered_map<string, City *> * connections;

	// Is there a research center in the city.
	bool researchCenter;
	
	// Total amount of cubes on the city (useful when infecting)
	int disease;

	// Breakdown of the different diseases in town (useful for curing)
	int blueDisease;
	int yellowDisease;
	int blackDisease;
	int redDisease;

public:

	// Different constructors to handle different cases (ex: debug). Normally, only the one with location and research should be used.
	City();
	City(Location * location, const bool research);
	City(Location * location, unordered_map<string, City *> * connections, const bool research);
	City(Location * location, unordered_map<string, City *> * connections, int disease, int blueDisease, int yellowDisease, int blackDisease,
		int redDisease, const bool research);
	~City();

	// Method to connect two cities. Uses pointers.
	void connect(City * city);

	// Unused atm. May be removed in the next iteration. Gives a lot of power.
	unordered_map<string, City *> * getConnections();

	// Returns the pointer to the location object attached to the city (name and region).
	Location * getLocation();

	// Shorter method to get the name of the city.
	string getName();

	// Setters and getters
	void setResearchCenter(const bool research);
	bool getResearchCenter();
	
	void setDisease(const int disease);
	int getDisease();

	void setBlueDisease(const int disease);
	int getBlueDisease();

	void setYellowDisease(const int disease);
	int getYellowDisease();

	void setBlackDisease(const int disease);
	int getBlackDisease();

	void setRedDisease(const int disease);
	int getRedDisease();

	// Used to demo the city object.
	void displayInfo();

};
// Here for serialization purpose.
template<class Archive>
inline void City::serialize(Archive & ar, const unsigned int version)
{
	ar & location;
	ar & researchCenter;
	ar & disease;
	ar & blueDisease;
	ar & yellowDisease;
	ar & blackDisease;
	ar & redDisease;
	ar & connections;
	ar & researchCities;
}