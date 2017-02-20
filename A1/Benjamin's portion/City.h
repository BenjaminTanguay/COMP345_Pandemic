#pragma once
#include "Location.h"
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;
class City
{
private:
	Location * location;
	unordered_map<string, City *> * connections;
	bool researchCenter;
	int disease;
	int blueDisease;
	int yellowDisease;
	int blackDisease;
	int redDisease;



public:
	City();
	City(Location * location, const bool research);
	City(Location * location, unordered_map<string, City *> * connections, const bool research);
	City(Location * location, unordered_map<string, City *> * connections, int disease, int blueDisease, int yellowDisease, int blackDisease,
		int redDisease, const bool research);
	~City();
	void connect(City * city);
	unordered_map<string, City *> * getConnections();
	Location * getLocation();
	string getName();
	void setResearchCenter(const bool research);
	bool getResearchCenter();
	void displayInfo();



};

