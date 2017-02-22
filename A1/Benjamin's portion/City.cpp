#include "City.h"
using namespace std;

// Assigning the static variable for the class.
vector<City *> * City::researchCities = new vector<City *>;
 
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
	City(location, connections, 0, 0, 0, 0, 0, research) {}
City::City(Location * location, unordered_map<string, City *> * connections, int disease, int blueDisease, int yellowDisease, int blackDisease, int redDisease, const bool research) :
	location(location), connections(connections), disease(disease), blueDisease(blueDisease), yellowDisease(yellowDisease), blackDisease(blackDisease), redDisease(redDisease) {
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
void City::connect(City * city)
{
	//We look to see if the city already exist in the connection map
	if (city->getConnections()->size() == 0 || city->getConnections()->at(this->getName()) != this) 
	{
		// If it doesn't, we create the connection in both city's maps.
		this->connections->emplace(city->getName(), city);
		city->getConnections()->emplace(this->getName(), this);
	}
}

// Returns the city's map of connections.
unordered_map<string, City *> * City::getConnections()
{
	return connections;
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
	this->researchCenter = research;
	// If there is a research center built, we loop through the cities with a research center and connect them to this new city. Then we add the new city to the list of research center cities.
	if (research) {
		if (this->researchCities->size() > 0) {
			for (unsigned i = 0; i < this->researchCities->size(); ++i) {
				this->connect(this->researchCities->at(i));
			}
		}
		this->researchCities->push_back(this);
	}
}

// Getters and setters
bool City::getResearchCenter()
{
	return this->researchCenter;
}

void City::setDisease(const int disease)
{
	this->disease = disease;
}

int City::getDisease()
{
	return this->disease;
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
	cout << "Disease cubes: " << this->disease << endl
		<< "Blue disease: " << this->blueDisease << endl
		<< "Yellow disease: " << this->yellowDisease << endl
		<< "Black disease: " << this->blackDisease << endl
		<< "Red disease: " << this->redDisease << endl << endl;
}




