#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>


using namespace std;

class GameStateVar
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	inline void GameStateVar::serialize(Archive & ar, const unsigned int version)
	{
		ar & blue;
		ar & yellow;
		ar & black;
		ar & red;
		ar & blueCure;
		ar & yellowCure;
		ar & blackCure;
		ar & redCure;
		ar & blueEradicated;
		ar & yellowEradicated;
		ar & blackEradicated;
		ar & redEradicated;
		ar & oneQuietNight;
		ar & eclosionCounter;
		ar & researchCenterCounter;
		ar & infectionRate;
		ar & infectionCounter;
	}



	int blue;
	int yellow;
	int black;
	int red;
	bool blueCure;
	bool yellowCure;
	bool blackCure;
	bool redCure;
	bool blueEradicated;
	bool yellowEradicated;
	bool blackEradicated;
	bool redEradicated;

	bool oneQuietNight;

	// Lose when eclosion = 8
	int eclosionCounter;

	// Number of research centers on the map
	int researchCenterCounter;

	// The number of infection cards to draw per turn
	int infectionRate;

	// The counter on which depends the number of infectino cards to draw per turn
	int infectionCounter;
	GameStateVar();
	~GameStateVar();

	void constructGameState();

public:
	static GameStateVar * getInstance();

	void reset();
	int getResearchCenterCounter();
	void incrementResearchCenterCounter();

	// Decrements the available cubes of the corresponding region by one.
	// Loss condition. Returns false if game is lost.
	bool decrementCube(int region, vector<string> * log);

	void incrementCube(int color);

	// Increments the eclosion counter and increase the infection counter.
	// Loss condition. Returns false if game is lost.
	bool incrementEclosion(vector<string> * log);

	// Manages the infection rate (how many cards drawn per turn) and infection counter
	void incrementInfection();

	bool getOneQuietNight();
	void setOneQuietNight(bool oneQuietNight);

	// Returns how many eclosions before the infection rate increases
	int infectionIncreaseIn();

	// Getters
	int getBlue();
	int getYellow();
	int getBlack();
	int getRed();
	int getEclosionCounter();
	int getInfectionRate();
	int getInfectionCounter();

	// Returns the cure state of any region.
	bool getCure(int region);

	// Set the cure of a specific color/region to true. If all cures are discovered, returns false and the game end. Else, returns true.
	bool setCure(int region);

	bool getEradicated(int region);

	void setEradicated(int region);

	int getDisease(int region);

	bool isGameWon();

	bool isGameLost();

	bool isGameOver();

};

