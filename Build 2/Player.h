// Benjamin Tanguay
// 40009113

#pragma once
#include "CityCard.h"
#include "EventCard.h"
#include <set>
#include <string>
#include "Card.h"
#include "Pawn.h"
#include "City.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "PlayMap.h"
#include "Session.h"
#include "ReferenceCard.h"
#include "RoleCard.h"
#include <random>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/set.hpp>


using namespace std;


struct compareSet {
	bool operator()(Card * a, Card * b) const {
		if (dynamic_cast<CityCard *>(a) != nullptr && dynamic_cast<CityCard *>(b) != nullptr) {
			return  (dynamic_cast<CityCard *>(a)->getLocation()->getRegion() 
				< dynamic_cast<CityCard *>(b)->getLocation()->getRegion())
				|| ((dynamic_cast<CityCard *>(a)->getLocation()->getRegion()
					== dynamic_cast<CityCard *>(b)->getLocation()->getRegion()
					&& dynamic_cast<CityCard *>(a)->getLocation()->getName() 
					< dynamic_cast<CityCard *>(b)->getLocation()->getName()));
		}
		else if (dynamic_cast<CityCard *>(a) != nullptr && dynamic_cast<EventCard *>(b) != nullptr) {
			return true;
		}
		else if (dynamic_cast<EventCard *>(a) != nullptr && dynamic_cast<EventCard *>(b) != nullptr) {
			return dynamic_cast<EventCard *>(a)->getTitle() < dynamic_cast<EventCard *>(b)->getTitle();
		}
		else if (dynamic_cast<EventCard *>(a) != nullptr && dynamic_cast<CityCard *>(b) != nullptr) {
			return false;
		}
		else {
			return true;
		}
	}
};

// The player class contains all the possessions of a player. Its methods represent the type of actions it can use.
// Eventually, the player could become an abstract class and the seven different player roles could be its child classes. Those child classes
// would override relevant methods to represent their special powers.
class Player
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void Player::serialize(Archive & ar, const unsigned int version)
	{
		ar & playerName;
		ar & playerId;
		ar & actionPoints;
		ar & playerRole;
		ar & pawn;
		ar & hand;
		ar & roleCard;
		ar & referenceCard;
		//ar & CONTINGENCY_PLANNER;
		//ar & OPERATION_EXPERT;
		//ar & DISPATCHER;
		//ar & QUARANTINE_SPECIALIST;
		//ar & RESEARCHER;
		//ar & MEDIC;
		//ar & SCIENTIST;
	}


	string playerName;
	int playerId;

	// To implement. Map was chosen because ordered iteration could be useful to represent the hand in the console or a GUI.
	// Ideally, will order by region and then by alphabetical order.
	// map<pair<int, string>, Card> * hand;

	// Number of actions can do;
	int actionPoints;

	// Here to represent the role card. Will be removed in other iterations.
	int playerRole;

	// Pawn contains a color and a city location.
	Pawn * pawn;

	// To implement
	// Card roleCard;
	// Card referenceCard;

	set<Card *, compareSet> * hand;

	
	RoleCard * roleCard;

public:
	// The roles are represented numerically to allow for easier arithmetic comparaison.

	static const int CONTINGENCY_PLANNER = 1;
	static const int OPERATION_EXPERT = 2;
	static const int DISPATCHER = 3;
	static const int QUARANTINE_SPECIALIST = 4;
	static const int RESEARCHER = 5;
	static const int MEDIC = 6;
	static const int SCIENTIST = 7;


	static ReferenceCard reference;

	// Relevant constructor. It mostly relays the info to the pawn object.
	Player(string name, City * origin);
	~Player();

	// Here to allow o forcefully set a different city to the pawn without the move command.
	void setLocation(City * city);

	// The different actions the player can have. Will need to be implemented in a subsequent iteration.
	string move(City * city); // Regular movement
	string move(CityCard * card); // Move to city on card
	string move(CityCard * card, City * city); // If card == current city, move to any city
	string build(CityCard * card); // Build center if hand has current city as card
	string treatDisease(int type); 
	string shareKnowledge(CityCard * card, Player * player);
	string discoverCure(CityCard * card1, CityCard * card2, CityCard * card3, CityCard * card4, CityCard * card5);
	void displayInfo();
	void draw(Card * card);

	string getPlayerName();

	string getPlayerRole();

	City * getCity();

	set<Card *, compareSet> * getHand();

	int getActionPoints();

	int getPlayerId();
	bool handContains(Card * card);

	void refreshActions();
	void discardCard(Card * card);

	// Temporary for demonstration.
	int getRole();

	RoleCard * getRoleCard();
};


