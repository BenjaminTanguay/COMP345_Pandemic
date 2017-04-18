#pragma once
#include "City.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <fstream>
#include <sys/stat.h>
#include "ConsoleFormat.h"
#include "Subject.h"


struct compareMap {
	bool operator()(Location * a, Location * b) const {
		return (a->getRegion() < b->getRegion()) || ((a->getRegion() == b->getRegion() && a->getName() < b->getName()));
	}
};

class PlayMap : public Subject
{
	// Here for serialization purpose. For this iteration, we only want to serialize the play map. Eventually, we may rework it so that the whole session is saved/restored.
	friend class boost::serialization::access;
	template<class Archive>
	inline void PlayMap::serialize(Archive & ar, const unsigned int version)
	{
		ar & origin;
		ar & playMap;
	}

	// The play map. It is an unordered_map to allow for O(1) operations when querying for a city.
	map<Location *, City *, compareMap> * playMap;
	
	// The origin is the city the players normally begin on. It starts with a research center. By default, it is the first location defined in the session.
	City * origin;
	PlayMap();
	PlayMap(City * origin);

	void resetCityVisits();
	void visitPlayMap(City * city);

public:
	static PlayMap * getInstance();
	static PlayMap * getInstance(City * origin);
	~PlayMap();

	void clearPlayMap();
	void addResearchCenter(Location * city);
	void setOrigin(Location * city);
	void setNewOrigin(Location * loc, bool researchCenter);

	map<Location *, City *, compareMap> * getPlayMap();
	City * PlayMap::getOrigin();


	bool connectedGraphCheck();

	bool maxNumberOfResearchCenterCheck();

	bool savePlayMap(string fileName);
	bool loadPlayMap(string fileName);
	bool minimumNumberOfCities();

};

