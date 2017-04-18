#include "PlayMap.h"



PlayMap::PlayMap()
{
	this->playMap = new map<Location *, City*, compareMap>;
}

PlayMap::PlayMap(City * origin)
{
	this->playMap = new map<Location *, City*, compareMap>;
	this->origin = origin;
}


PlayMap * PlayMap::getInstance()
{
	static PlayMap * instance = new PlayMap();

	return instance;
}

PlayMap * PlayMap::getInstance(City * origin)
{
	static PlayMap * instance = new PlayMap(origin);

	return instance;
}

PlayMap::~PlayMap()
{
	delete playMap;
	playMap = nullptr;
	delete origin;
	origin = nullptr;
}

map<Location *, City*, compareMap>* PlayMap::getPlayMap()
{
	return this->playMap;
}

// Simple interface implemented so that we can demonstrate the different functions of the classes in the main.
void PlayMap::clearPlayMap()
{
	origin = nullptr;
	this->playMap->clear();
}

void PlayMap::addResearchCenter(Location * city)
{
	this->playMap->at(city)->setResearchCenter(true);
}

// The origin is used to store the default location where players will begin on the play map. 
// By default, the origin point should have a research center.
void PlayMap::setOrigin(Location * city)
{
	this->origin->setResearchCenter(false);
	this->origin = this->playMap->at(city);
	this->origin->setResearchCenter(true);
}

void PlayMap::setNewOrigin(Location * loc, bool researchCenter) {
	this->origin = new City(loc, researchCenter);
}

City * PlayMap::getOrigin()
{
	return this->origin;
}

void PlayMap::visitPlayMap(City * city) {
	city->setVisited(true);
	for (auto iterate = city->getConnections()->begin(); iterate != city->getConnections()->end(); ++iterate) {
		if (!iterate->second->getVisited()) {
			visitPlayMap(iterate->second);
		}
	}
}

void PlayMap::resetCityVisits() {
	for (auto iterate = playMap->begin(); iterate != playMap->end(); ++iterate) {
		iterate->second->setVisited(false);
	}
}

bool PlayMap::connectedGraphCheck() {
	visitPlayMap(origin);
	bool temp = true;
	for (auto iterate = playMap->begin(); iterate != playMap->end(); ++iterate) {
		temp = temp && iterate->second->getVisited();
	}
	resetCityVisits();
	return temp;
}

bool PlayMap::maxNumberOfResearchCenterCheck() {
	int count = 0;
	for (auto iterate = playMap->begin(); iterate != playMap->end(); ++iterate) {
		if (iterate->second->getResearchCenter()) {
			++count;
		}
	}
	return count <= 6;
}

bool PlayMap::savePlayMap(string fileName)
{
	{
		ofstream outputStream(fileName);
		boost::archive::text_oarchive archive(outputStream);
		archive << *this;
	}
	return true;
}

bool PlayMap::loadPlayMap(string fileName)
{
	// Test if file access
	struct stat buffer;
	if (!stat(fileName.c_str(), &buffer) == 0) {
		return false;
	}
	else {
		{
			ifstream inputStream(fileName);
			boost::archive::text_iarchive unarchive(inputStream);
			unarchive >> *this;
		}
		return true;
	}
}

bool PlayMap::minimumNumberOfCities() {

	int count[4];
	count[0] = 0;
	count[1] = 0;
	count[2] = 0;
	count[3] = 0;
	bool temp = true;
	for (auto iterator = playMap->begin(); iterator != playMap->end(); ++iterator) {
		switch (iterator->first->getRegion()) {
		case 1:
			++count[0];
			break;
		case 2:
			++count[1];
			break;
		case 3:
			++count[2];
			break;
		case 4:
			++count[3];
			break;
		}
	}
	for (int i = 0; i < 4; ++i) {
		temp = temp && (count[i] == 0 || count[i] >= 5);
	}
	return temp;
}

