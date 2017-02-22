#include "Pawn.h"



Pawn::Pawn(const string color, const City & origin)
{
	this->city = origin;
	this->color = color;
}

// Getters and setters
City & Pawn::getCity()
{
	return city;
}

void Pawn::setCity(const City & city)
{
	this->city = city;
}

string & Pawn::getColor()
{
	return color;
}

void Pawn::setColor(const string color) 
{
	this->color = color;
}

// Used for demonstration and debug
void Pawn::displayInfo()
{
	cout << "Pawn color: " << color << endl
		<< "Pawn location: " << city.getLocation()->getName() << endl;
}
