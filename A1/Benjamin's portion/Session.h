// Benjamin Tanguay
// 40009113

#pragma once

#include "Location.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "City.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>

// The purpose of the session class is to hold all the data relevant to one pandemic game.
// It should hold the different decks, the infection rate, the different players, who's turn it is, what phase we're in, the play map, etc.
// Eventually, we should transform it so that it becomes a singleton.
class Session
{
private:

	// Here for serialization purpose. For this iteraiton, we only want to serialize the play map. Eventually, we may rework it so that the whole session is saved/restored.
	friend class boost::serialization::access;
	template<class Archive>
	inline void Session::serialize(Archive & ar, const unsigned int version)
	{
		ar & origin;
		ar & playMap;
	}

	// The collection of locations available in the game. Useful to create the decks of cards and the cities.
	vector<Location *> * locations;

	// The different players in the game.
	vector<Player *> * players;

	// The origin is the city the players normally begin on. It starts with a research center. By default, it is the first location defined in the session.
	City * origin;

	// The play map. It is an unordered_map to allow for O(1) operations when querying for a city.
	unordered_map<string, City *> * playMap;

	// State of the game. More variables will be added here.
	int playerTurn;
	int playerPhase;

public:

	Session();
	Session(City * origin);
	~Session();

	// Getters and setters
	City * getOrigin();
	vector<Player *> * getPlayers();
	int getPlayerTurn();
	int getPlayerPhase();
	void setPlayerTurn(int const turn);
	void setPlayerPhase(int const phase);

	// Simple interface implemented for the demonstration.
	void addLocation(const string name, const int region);
	void clearLocation();
	void addPlayer(string name, string color);
	void displayPlayersInfo();
	void displayCityInfo();
	void connectCity(string city1, string city2);
	void setOrigin(string cityName);
	void clearPlayMap();
	void clearPlayers();
	void addResearchCenter(string city);
	void savePlayMap(string fileName);
	void loadPlayMap(string fileName);

};



