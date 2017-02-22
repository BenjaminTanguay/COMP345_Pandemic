// Benjamin Tanguay
// 40009113

#pragma once
#include <map>
#include <string>
#include "Card.h"
#include "Pawn.h"
#include "City.h"
#include <algorithm>
#include <ctime> 
#include <cstdlib> 

using namespace std;

// The player class contains all the possessions of a player. Its methods represent the type of actions it can use.
// Eventually, the player could become an abstract class and the seven different player roles could be its child classes. Those child classes
// would override relevant methods to represent their special powers.
class Player
{
private:
	string playerName;
	int playerId;

	// To implement. Map was chosen because ordered iteration could be useful to represent the hand in the console or a GUI.
	// Ideally, will order by region and then by alphabetical order.
	map<pair<int, string>, Card> * hand;

	// Number of actions can do;
	int actionPoints;

	// Here to represent the role card. Will be removed in other iterations.
	int playerRole;

	// Pawn contains a color and a city location.
	Pawn * pawn;

	// To implement
	Card roleCard;
	Card referenceCard;

public:
	// The roles are represented numerically to allow for easier arithmetic comparaison.

	static const int CONTINGENCY_PLANNER = 1;
	static const int OPERATION_EXPERT = 2;
	static const int DISPATCHER = 3;
	static const int QUARANTINE_SPECIALIST = 4;
	static const int RESEARCHER = 5;
	static const int MEDIC = 6;
	static const int SCIENTIST = 7;


	// Relevant constructor. It mostly relays the info to the pawn object.
	Player(string name, string color, const City & origin);
	~Player();

	// The different actions the player can have. Will need to be implemented in a subsequent iteration.
	void move(const City & city); // Regular movement
	void move(const Card & card); // Move to city on card
	void move(const Card & card, const City & city); // If card == current city, move to any city
	void build(const Card & card); // Build center if hand has current city as card
	void treatDisease(); 
	void shareKnowledge();
	void discoverCure(const Card & card1, const Card & card2, const Card & card3, const Card & card4, const Card & card5);
	void displayInfo();

};

