#include <iostream>
#include <fstream>
#include "Location.h"
#include "Player.h"
#include "Session.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace std;


int main() {
	Session * session = new Session();
	
	session->addLocation("Montreal", 1);
	session->addLocation("Atlanta", 1);
	session->addLocation("Beijing", 4);
	session->addLocation("Paris", 1);
	session->addLocation("Cairo", 3);
	session->addLocation("Mexico city", 2);
	
	session->addPlayer("Nepherius", "Blue");
	session->addPlayer("Mymy", "Red");
	session->connectCity("Montreal", "Paris");
	session->connectCity("Montreal", "Atlanta");
	session->connectCity("Beijing", "Cairo");
	session->displayPlayersInfo();
	session->displayCityInfo();
	
	cout << "TRYING TO SERIALIZE" << endl;
	
	{
	ofstream outputStream("save.txt");
	boost::archive::text_oarchive archive(outputStream);
	archive << session;
	}
	session->clearPlayMap();
	session->displayCityInfo();

	{
	ifstream inputStream("save.txt");
	boost::archive::text_iarchive unarchive(inputStream);
	unarchive >> session;
	}
	
	session->displayCityInfo();

	cin.get();
	return 0;
}