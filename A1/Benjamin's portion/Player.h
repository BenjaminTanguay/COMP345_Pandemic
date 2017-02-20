#pragma once
#include <map>
#include <string>
#include "Card.h"
#include "Pawn.h"
#include "City.h"
#include <random>

using namespace std;

class Player
{
public:

	static const int CONTINGENCY_PLANNER = 1;
	static const int OPERATION_EXPERT = 2;
	static const int DISPATCHER = 3;
	static const int QUARANTINE_SPECIALIST = 4;
	static const int RESEARCHER = 5;
	static const int MEDIC = 6;
	static const int SCIENTIST = 7;


	Player(string name, string color, const City & origin);
	~Player();
	void move(const City & city); // Regular movement
	void move(const Card & card); // Move to city on card
	void move(const Card & card, const City & city); // If card == current city, move to any city
	void build(const Card & card); // Build center if hand has current city as card
	void treatDisease(); 
	void shareKnowledge();
	void discoverCure(const Card & card1, const Card & card2, const Card & card3, const Card & card4, const Card & card5);
	void displayInfo();

private:
	string playerName;
	int playerId;
	map<pair<int, string>, Card> * hand; // The hand orders the cards by region (int) then by string name if possible.
	int actionPoints;
	int playerRole;
	Pawn * pawn;
	void shuffle(int array[], int length);


};

