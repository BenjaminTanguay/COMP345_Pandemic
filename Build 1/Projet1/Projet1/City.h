// Benjamin Tanguay
// 40009113

#pragma once
#include "Location.h"
#include <string>
#include <algorithm>
#include <unordered_map>
#include "GameStateVar.h"
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

	unordered_map<string, City *> * researchConnections;

	// Is there a research center in the city.
	bool researchCenter;

	// Breakdown of the different diseases in town (useful for curing)
	int blueDisease;
	int yellowDisease;
	int blackDisease;
	int redDisease;

	// Used to test if a city is already connected to another city.
	bool contains(City * city, int connection);

	unordered_map<string, City *> * getLocalConnections(int connection);
	static unordered_map<string, City *> * getForeignConnections(City * city, int connection);

	vector<bool> players;
	bool visited;


	

public:
	string diseaseTranslate(int region);
	// For internal use to differenciate between the regular connection unordered_map and the research connection unordered_map
	static const int REGULAR_CONNECTION = 1;
	static const int RESEARCH_CONNECTION = 2;

	// Different constructors to handle different cases (ex: debug). Normally, only the one with location and research should be used.
	City();
	City(Location * location, const bool research);
	City(Location * location, unordered_map<string, City *> * connections, const bool research, vector<bool> players);
	City(Location * location, unordered_map<string, City *> * connections, int blueDisease, int yellowDisease, int blackDisease,
		int redDisease, const bool research, vector<bool> players, unordered_map<string, City*> * researchConnections);
	~City();

	// Method to connect two cities. Uses pointers.
	static void connect(City * city1, City * city2, int connection);

	// Method to remove a connection between two cities. Uses pointers. Used for demonstration and debug purposes.
	void disconnect(City * city, int connection);

	// Unused atm. May be removed in the next iteration. Gives a lot of power.
	unordered_map<string, City *> * getConnections();
	unordered_map<string, City *> * getResearchConnections();

	// Returns the pointer to the location object attached to the city (name and region).
	Location * getLocation();

	// Shorter method to get the name of the city.
	string getName();

	// Setters and getters
	void setResearchCenter(const bool research);
	bool getResearchCenter();

	void setBlueDisease(const int disease);
	int getBlueDisease();

	void setYellowDisease(const int disease);
	int getYellowDisease();

	void setBlackDisease(const int disease);
	int getBlackDisease();

	void setRedDisease(const int disease);
	int getRedDisease();

	int getDisease(int region);

	void setVisited(bool flag);

	bool getVisited();

	bool incrementDisease(int color);
	void decrementDisease(int color);

	// Used to demo the city object.
	void displayInfo();

	bool infect(unordered_map<string, City *> * city, int color, vector<string> * log);

	int getPlayer();

	void setPlayer(int index, bool value);

	bool containPlayer(unsigned index);

	bool operator>(City * city) const;

	bool operator<(City * city) const;

	bool isConnected(City * city);

	static vector<City *> * getResearchCitiesList();

	void initializePlayerFlags();

};
// Here for serialization purpose.
template<class Archive>
inline void City::serialize(Archive & ar, const unsigned int version)
{
	ar & location;
	ar & researchCenter;
	ar & blueDisease;
	ar & yellowDisease;
	ar & blackDisease;
	ar & redDisease;
	ar & connections;
	ar & researchCities;
	ar & researchConnections;
	ar & players;
	ar & visited;
}