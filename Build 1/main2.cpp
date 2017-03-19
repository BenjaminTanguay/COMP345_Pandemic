#include <iostream>
#include <fstream>
#include "Location.h"
#include "Player.h"
#include "Session.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "main.h"
#include <QtWidgets/QApplication>

using namespace std;

/*
int main(int argc, char *argv[]) {

	Session * session = new Session();
	
	session->addLocation("Montreal", 1);
	session->addLocation("Atlanta", 1);
	session->addLocation("Beijing", 4);
	session->addLocation("Paris", 1);
	session->addLocation("Cairo", 3);
	session->addLocation("Mexico city", 2);
	session->connectCity("Montreal", "Paris");
	session->connectCity("Montreal", "Atlanta");
	session->connectCity("Beijing", "Cairo");

	PlayerDeck * playerDeck = session->getPlayerDeck();
	InfectionDeck * infectionDeck = session->getInfectionDeck();

	
	
	

	cout << "====================================================================" << endl;

	cout << "Adding players with default origin as the first entered location (here: Montreal)" << endl << endl;

	session->addPlayer("Benjamin", "Blue");
	session->addPlayer("Nick", "Red");

	session->displayPlayersInfo();

	cout << "====================================================================" << endl;

	cout << "Modifying the origin of the players (Paris)." << endl << endl;

	session->setOrigin("Paris");
	session->displayPlayersInfo();

	cout << "====================================================================" << endl;

	session->displayCityInfo();

	cout << "====================================================================" << endl;

	cout << "TRYING TO SERIALIZE" << endl
		<< "Saving the playMap to a file" << endl << endl;
	
	session->savePlayMap("file");

	cout << "Deleting the cities from the session object" << endl << endl;

	session->clearPlayMap();

	cout << "Trying to display the deleted cities:" << endl;

	session->displayCityInfo();

	cout << endl << "Loading the serialized file to session." << endl << endl;

	session->loadPlayMap("file");

	cout << "Displaying the restored cities informations" << endl << endl;

	session->displayCityInfo();

	cout << "End of demonstration" << endl;

	cin.get();



}
*/