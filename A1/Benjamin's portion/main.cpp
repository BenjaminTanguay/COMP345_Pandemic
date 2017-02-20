#include <iostream>
#include "Location.h"
#include "Player.h"
#include "Session.h"
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
	session->connectCity("Beijing", "Cairo");
	session->displayPlayersInfo();
	session->displayCityInfo();
	cin.get();
	return 0;
}