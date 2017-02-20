#pragma once
#include "Location.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Player.h"
#include "City.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


class Session
{
public:
	
	~Session();

	City * getOrigin();
	unordered_map<string, City> * getPlayMap();
	vector<Location> * getLocations();
	vector<Player *> * getPlayers();
	int getPlayerTurn();
	int getPlayerPhase();
	void setPlayerTurn(int const turn);
	void setPlayerPhase(int const phase);
	void addLocation(const string name, const int region);
	void clearLocation();
	void addPlayer(string name, string color);
	void displayPlayersInfo();
	void displayCityInfo();
	Session(City * origin);
	Session();
	void connectCity(string city1, string city2);


private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version);

	vector<Location *> * locations;
	vector<Player *> * players;
	int playerTurn;
	int playerPhase;
	City * origin;
	unordered_map<string, City *> * playMap;

};

template<class Archive>
inline void Session::serialize(Archive & ar, const unsigned int version) 
{
	ar & playerTurn;
	ar & locations;
	ar & playerPhase;
	ar & origin;
	ar & playMap;
	ar & players;
}
