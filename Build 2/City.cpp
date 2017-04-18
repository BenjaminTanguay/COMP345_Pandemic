#include "City.h"
using namespace std;

// Assigning the static variable for the class.
vector<City *> * City::researchCities = new vector<City *>;

bool City::contains(City * city, int connection)
{
	if (getLocalConnections(connection)->size() != 0) {
		if (getLocalConnections(connection)->find(city->getName()) == getLocalConnections(connection)->end()) {
			return false;
		}
		else
		{
			return true;
		}
	}
	else {
		return false;
	}
}

unordered_map<string, City*>* City::getLocalConnections(int connection)
{
	switch (connection) {
	case 1:
		return this->connections;
	case 2:
		return this->researchConnections;
	default:
		return nullptr;
	}
}

unordered_map<string, City*>* City::getForeignConnections(City * city, int connection)
{
	switch (connection) {
	case 1:
		return city->getConnections();
	case 2:
		return city->getResearchConnections();
	default:
		return nullptr;
	}
}

void City::initializePlayerFlags()
{
	for (unsigned i = 0; i < 4; ++i) {
		players.push_back(false);
	}
}

string City::diseaseTranslate(int region)
{
	switch (region) {
	case 1:
		return "blue disease";
	case 2:
		return "yellow disease";
	case 3:
		return "black disease";
	case 4:
		return "red disease";
	default:
		return "";
	}
}

// Here for the future if we want to use it.
City::City()
{
}

// Only the first constructor should be useful. Other two are here to give more control of the city class (for debug).
City::City(Location * location, const bool research) :
	location(location), connections(new unordered_map<string, City *>), researchConnections(new unordered_map<string, City*>) {
	this->setResearchCenter(research);
	initializePlayerFlags();
	visited = false;
}
City::City(Location * location, unordered_map<string, City *> * connections, const bool research, vector<bool> players) :
	City(location, connections, 0, 0, 0, 0, research, players, new unordered_map<string, City *>) {
	initializePlayerFlags();
	visited = false;
}
City::City(Location * location, unordered_map<string, City *> * connections, int blueDisease, int yellowDisease, int blackDisease, int redDisease, const bool research, vector<bool> players, unordered_map<string, City*> * researchConnections) :
	location(location), connections(connections), blueDisease(blueDisease), yellowDisease(yellowDisease), blackDisease(blackDisease), redDisease(redDisease), players(players), researchConnections(researchConnections){
	this->setResearchCenter(research);
	visited = false;
}

// Destructor
City::~City()
{
	delete connections;
	connections = nullptr;
	
	delete location;
	location = nullptr;
	
	delete researchConnections;
	researchConnections = nullptr;

	delete researchCities;
	researchCities = nullptr;
}


//Method allowing to connect cities together. Works with city pointers.
void City::connect(City * city1, City * city2, int connection)
{
	//We look to see if the city already exist in the connection map
	if (getForeignConnections(city1, connection)->size() == 0 || getForeignConnections(city1, connection)->find(city2->getLocation()->getName()) == getForeignConnections(city1, connection)->end()){
		// If it doesn't, we create the connection in both city's maps.
		
		getForeignConnections(city1, connection)->emplace(city2->getName(), city2);
		getForeignConnections(city2, connection)->emplace(city1->getName(), city1);
	}
}

void City::disconnect(City * city, int connection)
{
	if (this->contains(city, connection)) {
		getForeignConnections(city, connection)->erase(this->getName());
		getLocalConnections(connection)->erase(city->getName());
	}
}

// Returns the city's map of connections.
unordered_map<string, City *> * City::getConnections()
{
	return this->connections;
}

unordered_map<string, City*>* City::getResearchConnections()
{
	return this->researchConnections;
}

// Gets the city location (name and region)
Location * City::getLocation()
{
	return location;
}

// Shorter method to get the city name.
string City::getName()
{
	return location->getName();
}

//Used to make sure a city that gets a research center built gets the proper connections.
void City::setResearchCenter(const bool research)
{
	bool temp = this->researchCenter;
	this->researchCenter = research;
	// If there is a research center built, we loop through the cities with a research center and connect them to this new city. Then we add the new city to the list of research center cities.
	if (research && !temp) {
		if (this->researchCities->size() > 0) {
			GameStateVar::getInstance()->incrementResearchCenterCounter();
			for (unsigned i = 0; i < this->researchCities->size(); ++i) {
				connect(this->researchCities->at(i), this, RESEARCH_CONNECTION);
			}
		}
		this->researchCities->push_back(this);
	}
	else if (!research && temp) {
		for (unsigned i = 0; i < researchCities->size(); ++i) {
			if (researchCities->at(i) == this) {
				researchCities->erase(researchCities->begin() + i);
				delete this->researchConnections;
				researchConnections = new unordered_map<string, City *>;
				--i;
			}
			else {
				researchConnections->erase(this->getName());
			}
		}
	}
}

// Getters and setters
bool City::getResearchCenter()
{
	return this->researchCenter;
}

void City::setBlueDisease(const int disease)
{
	this->blueDisease = disease;
}

int City::getBlueDisease()
{
	return this->blueDisease;
}

void City::setYellowDisease(const int disease)
{
	this->yellowDisease = disease;
}

int City::getYellowDisease()
{
	return this->yellowDisease;
}

void City::setBlackDisease(const int disease)
{
	this->blackDisease = disease;
}

int City::getBlackDisease()
{
	return this->blackDisease;
}

void City::setRedDisease(const int disease)
{
	this->redDisease = disease;
}

int City::getRedDisease()
{
	return this->redDisease;
}

int City::getDisease(int region)
{
	switch (region) {
	case 1:
		return this->blueDisease;
	case 2:
		return this->yellowDisease;
	case 3:
		return this->blackDisease;
	case 4:
		return this->redDisease;
	default:
		return 0;
	}
	return 0;
}

void City::setVisited(bool flag) {
	visited = flag;
}

bool City::getVisited() {
	return visited;
}

bool City::isDiseased()
{
	return !(getDisease(1) == 0 &&
		getDisease(2) == 0 &&
		getDisease(3) == 0 &&
		getDisease(4) == 0);
}


bool City::incrementDisease(int color)
{
	switch (color) {
	case 1:
		if (this->blueDisease == 3) {
			return false;
		}
		else {
			++blueDisease;
			return true;
		}
		break;
	case 2:
		if (this->yellowDisease == 3) {
			return false;
		}
		else {
			++yellowDisease;
			return true;
		}
		break;
	case 3:
		if (this->blackDisease == 3) {
			return false;
		}
		else {
			++blackDisease;
			return true;
		}
		break;
	case 4:
		if (this->redDisease == 3) {
			return false;
		}
		else {
			++redDisease;
			return true;
		}
		break;
	}
	
	return false;
}

void City::decrementDisease(int color)
{
	switch (color) {
	case 1:
		--blueDisease;
		GameStateVar::getInstance()->incrementCube(color);
		break;
	case 2:
		--yellowDisease;
		GameStateVar::getInstance()->incrementCube(color);
		break;
	case 3:
		--blackDisease;
		GameStateVar::getInstance()->incrementCube(color);
		break;
	case 4:
		--redDisease;
		GameStateVar::getInstance()->incrementCube(color);
		break;
	}
}

// Used for demo and debug
void City::displayInfo()
{
	cout << "City:" << endl << endl;
	this->location->displayInfo();
	cout << "City connections: ";
	if (this->connections->size() == 0) {
		cout << "No connections";
	}
	else {
		for (auto iterate = this->connections->begin(); iterate != this->connections->end(); ++iterate) {
			cout << iterate->second->getName() << "    ";
		}
	}
	cout << endl;
	cout << "Blue disease: " << this->blueDisease << endl
		<< "Yellow disease: " << this->yellowDisease << endl
		<< "Black disease: " << this->blackDisease << endl
		<< "Red disease: " << this->redDisease << endl << endl;
}

bool City::infect(unordered_map<string, City *> * city, int color, vector<string> * log)
{
	// If a cube of the color is available, we go in. Else, we return false and the game ends.
	if (GameStateVar::getInstance()->decrementCube(color, log)) {

		// Here we try to increment the value of the disease. If there are already 3 cubes of the color we want to increase,
		// we return false and create an eclosion.
		if (this->incrementDisease(color)) {
			log->push_back(diseaseTranslate(color) + " incremented to " + to_string(getDisease(color)));
			return true;
		}

		// ECLOSION CODE
		else {
			log->push_back("Eclosion in " + location->getName());
			// Since we have an eclosion, we call the incrementInclosion method of the GameStateVar class.
			GameStateVar::getInstance()->incrementEclosion(log);
			// First we put our city in the hashmap passed as a param. The idea is that we don't two cities to keep triggering each other.
			// Once a city has had an eclosion, it is immune from the chain effect.
			city->emplace(this->getName(), this);

			bool temp = true;

			// We iterate through the connections of the city.
			for (auto iterator = this->connections->begin(); iterator != this->connections->end(); ++iterator) {
				
				// Here we check to see if the current position in the iteration is found in the map of the cities that already had an eclosion
				if (!(city->find(iterator->second->getName()) == city->end())) {
					
					// If it isn't found, then we infect that city. This way, we'll infect all cities that have a direct connection to the city that had an eclosion.
					// In case we reach a game losing situation, we store the boolean value returned by the infect method (remember, false = gameloss)
					temp = iterator->second->infect(city, color, log);
				}
				// If the game is loss, we break of the loop and return the value.
				if (!temp) {
					break;
				}
			}
			return temp;
		}
	}

	return false;
}

int City::getPlayer() {
	int numberOfPlayers = 0;
	for (unsigned i = 0; i < this->players.size(); ++i) {
		if (this->players.at(i)) {
			++numberOfPlayers;
		}
	}
	return numberOfPlayers;
}

void City::setPlayer(int index, bool value)
{
	this->players.at(index) = value;
}

bool City::containPlayer(unsigned index) {
	if (this->players.size() > index && index >= 0) {
		return this->players.at(index);
	}
	return false;
}

bool City::operator>(City * city) const
{
	return this->location > city->getLocation();
}

bool City::operator<(City * city) const
{
	return this->location < city->getLocation();
}

bool City::isConnected(City * city) {
	return (getLocalConnections(1)->find(city->getName()) != getLocalConnections(1)->end())
		|| (getLocalConnections(2)->find(city->getName()) != getLocalConnections(2)->end());
}

vector<City*>* City::getResearchCitiesList()
{
	return researchCities;
}



