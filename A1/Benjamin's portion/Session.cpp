#include "Session.h"


// Initialize the objects that needs to go on the heap.
Session::Session()
{
	this->locations = new vector<Location *>;
	this->playMap = new unordered_map<string, City *>;
	this->players = new vector<Player *>;
}

// The origin is used to store the default location where players will begin on the play map. 
// By default, the origin point should have a research center.
void Session::setOrigin(string cityName)
{
	this->origin->setResearchCenter(false);
	this->origin = this->playMap->at(cityName);
	this->origin->setResearchCenter(true);
}

Session::Session(City * origin)
{
	this->origin = origin;
}

Session::~Session()
{
	delete origin;
	origin = NULL;
	delete playMap;
	playMap = NULL;
	delete players;
	players = NULL;
	delete locations;
	locations = NULL;
}

// The origin is used to store the default location where players will begin on the play map.
City * Session::getOrigin()
{
	return origin;
}

// Setters and getters
vector<Player *> * Session::getPlayers()
{
	return this->players;
}

int Session::getPlayerTurn()
{
	return playerTurn;
}

int Session::getPlayerPhase()
{
	return playerPhase;
}

void Session::setPlayerTurn(int const turn)
{
	this->playerTurn = turn;
}

void Session::setPlayerPhase(int const phase)
{
	this->playerPhase = phase;
}


// Simple interface implemented so that we can demonstrate the different functions of the classes in the main.
void Session::clearPlayMap()
{
	this->playMap->clear();
}

void Session::addLocation(const string name, const int region)
{
	Location * loc = new Location(name, region);
	this->locations->push_back(loc);
	if (this->locations->size() == 1) {
		this->origin = new City(loc, true);
		this->playMap->emplace(loc->getName(), this->origin);
	}
	else {
		this->playMap->emplace(loc->getName(), new City(loc, false));
	}
}

void Session::clearLocation()
{
	this->locations->clear();
}

void Session::connectCity(string city1, string city2)
{
	this->playMap->at(city1)->connect(this->playMap->at(city2));
}

void Session::addPlayer(string name, string color)
{
	City & city = *(this->origin);
	this->players->push_back(new Player(name, color, city));
}

void Session::displayPlayersInfo()
{
	for (auto player : *(this->players)) {
		player->displayInfo();
	}
}

void Session::displayCityInfo()
{
	if (this->playMap->size() == 0) {
		cout << "No city defined" << endl;
	}
	else {
		for (auto iterate = this->playMap->begin(); iterate != this->playMap->end(); ++iterate) {
			iterate->second->displayInfo();
		}
	}
}





