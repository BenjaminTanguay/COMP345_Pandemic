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
#include "InfectionDeck.h"
#include "PlayerDeck.h"
#include "CityCard.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/tracking.hpp>
#include "PlayMap.h"
#include "Subject.h"
#include "RoleCard.h"
#include "Log.h"

class Player;
class PlayerDeck;
// The purpose of the session class is to hold all the data relevant to one pandemic game.
// It should hold the different decks, the infection rate, the different players, who's turn it is, what phase we're in, the play map, etc.
// Eventually, we should transform it so that it becomes a singleton.
class Session : public Subject
{
private:

	friend class boost::serialization::access;
	template<class Archive>
	inline void serialize(Archive & ar, const unsigned int version)
	{
		ar.register_type(static_cast<EventCard *>(NULL));
		ar.register_type(static_cast<CityCard *>(NULL));
		ar.register_type(static_cast<EpidemicCard *>(NULL));
		ar & playerDeck;
		ar & cityCards;
		ar & eventCards;
		ar & locations;
		ar & numberOfLocationsPerRegion;
		ar & playMap;
		ar & infectionDeck;
		ar & numberOfRegionsInPlay;
		ar & currentPlayer;
		ar & playerTurn;
		ar & playerPhase;
		ar & difficultyLevel;
		ar & log;
	}


	// The collection of locations available in the game. Useful to create the decks of cards and the cities.
	unordered_map<string, Location *> * locations;

	unordered_map<string, CityCard *> * cityCards;

	unordered_map<string, EventCard *> * eventCards;

	int numberOfLocationsPerRegion[4];

	// The different players in the game.
	vector<Player *> * players;

	unsigned currentPlayer;

	int numberOfRegionsInPlay;

	// The play map. It is an unordered_map to allow for O(1) operations when querying for a city.
	PlayMap * playMap;

	PlayerDeck * playerDeck;
	InfectionDeck * infectionDeck;

	Log * log;

	// State of the game. More variables will be added here.
	int playerTurn;
	int playerPhase;


	// Helper method to generate the cards with a location
	void generateCards(Location * loc);

	Session();
	Session(City * origin);
	~Session();

	int difficultyLevel;

public:

	static Session * getInstance();
	static Session & getInstance(City * origin);

	void resetSession();

	// Getters and setters
	City * getOrigin();
	vector<Player *> * getPlayers();
	int getPlayerTurn();
	int getPlayerPhase();
	void setPlayerTurn(int const turn);
	void setPlayerPhase(int const phase);
	void setDifficultyLevel(int const difficultyLevel);
	int getDifficultyLevel();

	// Simple interface implemented for the demonstration.
	void addLocation(const string name, const int region);
	void clearLocation();
	void connectCity(string city1, string city2, bool notify);
	void addPlayer(string name);
	void displayPlayersInfo();
	void displayCityInfo();
	void connectCity(Location * city1, Location * city2, bool notify);
	void setOrigin(Location * cityName);
	void clearPlayMap();
	void clearPlayers();
	void addResearchCenter(Location * city);
	bool savePlayMap(string fileName);
	bool loadPlayMap(string fileName);
	bool saveSession(string fileName);
	bool loadSession(string fileName);
	InfectionDeck * getInfectionDeck();
	PlayerDeck * getPlayerDeck();
	CityCard * getCityCards(string name);

	bool infect(Location * city, int numberOfInfections, int region, vector<string> * log);
	void initializeInfections();
	bool infectionDraw(vector<string> * log);
	bool drawFromInfectionDeck(vector<string>* log);
	bool playerDraw(unsigned index);
	void initializeHands(vector<string> * log);
	map<Location *, City *, compareMap> * getPlayMap();

	int getCurrentPlayer();
	City * getCity(string name);
	unordered_map<string, Location*>* getLocation();
	void incrementCurrentPlayer();

	void move(City * city);
	void move(CityCard * card);
	void move(CityCard * card, City * city); 
	void build(CityCard * card, City * city);
	void treatDisease(int type);
	void shareKnowledge(CityCard * card, Player * player);
	void discoverCure(CityCard * card1, CityCard * card2, CityCard * card3, CityCard * card4, CityCard * card5);

	void consultReference();

	void consultRoleCard();

	void addEventCards(EventCard * card);
	EventCard * getEventCard(string card);

	int getNumberOfRegionInPlay();
	int getNumberOfLocations(int region);

	Log * getLog();


};

BOOST_CLASS_TRACKING(Session, boost::serialization::track_always)


