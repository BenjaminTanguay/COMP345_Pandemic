#include "Pawn.h"



Pawn::Pawn(City * origin)
{
	this->city = origin;
}

// Getters and setters
City * Pawn::getCity()
{
	return city;
}

void Pawn::setCity(City * city)
{
	this->city = city;
}

// Used for demonstration and debug
void Pawn::displayInfo()
{
	cout << "Pawn location: " << city->getLocation()->getName() << endl;
}
