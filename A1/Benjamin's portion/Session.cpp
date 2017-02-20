#include "Session.h"


Session::Session()
{
	this->locations = new vector<Location *>;
	this->playMap = new unordered_map<string, City *>;
	this->players = new vector<Player *>;

}

void Session::connectCity(string city1, string city2)
{
	//City * city = this->playMap->at(city1);

	//cout << "DEBUG CITY MONTREAL" << endl;
	//city->displayInfo();
	this->playMap->at(city1)->connect(this->playMap->at(city2));
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

City * Session::getOrigin()
{
	return origin;
}

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


