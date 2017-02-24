#include "City.h"
using namespace std;

// Assigning the static variable for the class.
vector<City *> * City::researchCities = new vector<City *>;
 
bool City::contains(City * city, int connection)
{
	unordered_map<string, City *> * localConnections = getLocalConnections(connection);
	if (localConnections->size() != 0) {
		if (localConnections->find(city->getName()) == localConnections->end()) {
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

// Here for the future if we want to use it.
City::City()
{
}

// Only the first constructor should be useful. Other two are here to give more control of the city class (for debug).
City::City(Location * location, const bool research) :
	location(location), connections(new unordered_map<string, City *>){
	this->setResearchCenter(research);
}
City::City(Location * location, unordered_map<string, City *> * connections, const bool research) :
	City(location, connections, 0, 0, 0, 0, research) {}
City::City(Location * location, unordered_map<string, City *> * connections, int blueDisease, int yellowDisease, int blackDisease, int redDisease, const bool research) :
	location(location), connections(connections), blueDisease(blueDisease), yellowDisease(yellowDisease), blackDisease(blackDisease), redDisease(redDisease) {
	this->setResearchCenter(research);
}

// Destructor
City::~City()
{
	delete connections;
	connections = NULL;
	delete location;
	location = NULL;
}


//Method allowing to connect cities together. Works with city pointers.
void City::connect(City * city, int connection)
{
	unordered_map<string, City *> * localConnections = getLocalConnections(connection);
	unordered_map<string, City *> * foreignConnections = getForeignConnections(city, connection);

	//We look to see if the city already exist in the connection map
	if (foreignConnections->size() == 0 || foreignConnections->at(this->getName()) != this) 
	{
		// If it doesn't, we create the connection in both city's maps.
		localConnections->emplace(city->getName(), city);
		foreignConnections->emplace(this->getName(), this);
	}
}

void City::disconnect(City * city, int connection)
{
	unordered_map<string, City *> * localConnections = getLocalConnections(connection);
	unordered_map<string, City *> * foreignConnections = getForeignConnections(city, connection);
	
	if (this->contains(city, connection)) {
		foreignConnections->erase(this->getName());
		localConnections->erase(city->getName());
	}
}

// Returns the city's map of connections.
unordered_map<string, City *> * City::getConnections()
{
	return connections;
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
			for (unsigned i = 0; i < this->researchCities->size(); ++i) {
				this->connect(this->researchCities->at(i), RESEARCH_CONNECTION);
			}
		}
		this->researchCities->push_back(this);
	}
	else if (!research && temp) {
		for (unsigned i = 0; i < researchCities->size(); ++i) {
			if (researchCities->at(i) == this) {
				researchCities->erase(researchCities->begin() + i);
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

bool City::infect(unordered_map<string, City *> * city, int color)
{
	GameStateVar * gameState = GameStateVar::getInstance();

	// If a cube of the color is available, we go in. Else, we return false and the game ends.
	if (gameState->decrementCube(color)) {

		// Here we try to increment the value of the disease. If there are already 3 cubes of the color we want to increase,
		// we return false and create an eclosion.
		if (this->incrementDisease(color)) {
			return true;
		}

		// ECLOSION CODE
		else {
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
					temp = iterator->second->infect(city, color);
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




