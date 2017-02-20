#include "Pawn.h"



Pawn::Pawn(const string color, const City & origin)
{
	this->city = origin;
	this->color = color;
}


Pawn::~Pawn()
{
}

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

void Pawn::displayInfo()
{
	cout << "Pawn color: " << color << endl
		<< "Pawn location: " << city.getLocation()->getName() << endl;
}
