#include "City.h"
using namespace std;



City::City()
{
}

City::City(Location * location, const bool research) :
	location(location), connections(new unordered_map<string, City *>), researchCenter(research) {}
City::City(Location * location, unordered_map<string, City *> * connections, const bool research) :
	City(location, connections, 0, 0, 0, 0, 0, research) {}
City::City(Location * location, unordered_map<string, City *> * connections, int disease, int blueDisease, int yellowDisease, int blackDisease, int redDisease, const bool research) :
	location(location), connections(connections), disease(disease), blueDisease(blueDisease), yellowDisease(yellowDisease), blackDisease(blackDisease), redDisease(redDisease), researchCenter(research) {}


City::~City()
{
	delete connections;
	connections = NULL;
	delete location;
	location = NULL;
}

void City::connect(City * city)
{
	//unordered_map<string, City *> * targetCityConnect = city->getConnections();
	if (city->getConnections()->size() == 0 || city->getConnections()->at(this->getName()) != this) //We look to see if the city already exist in the map
	{
		// If it doesn't, we create the connection in both city's maps.
		this->connections->emplace(city->getName(), city);
		city->getConnections()->emplace(this->getName(), this);
	}
}

unordered_map<string, City *> * City::getConnections()
{
	return connections;
}

Location * City::getLocation()
{
	return location;
}

string City::getName()
{
	return location->getName();
}

void City::setResearchCenter(const bool research)
{
	this->researchCenter = research;
}

bool City::getResearchCenter()
{
	return this->researchCenter;
}

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


