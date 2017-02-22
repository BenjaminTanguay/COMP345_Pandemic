#include "Location.h"


// Default constructor. Not used but I kept it here in case it is needed.
Location::Location()
{
}

// Real constructor that should be used.
Location::Location(const string name, const int region)
{
	this->name = name;
	this->region = region;
}

// Setters and getters
string Location::getName()
{
	return name;
}

int Location::getRegion()
{
	return region;
}

void Location::setName(const string name)
{
	this->name = name;
}

void Location::setRegion(const int region)
{
	this->region = region;
}

// Used for debug and demo.
void Location::displayInfo()
{
	string temp;
	switch (region) {
	case 1:
		temp = "Blue";
		break;
	case 2:
		temp = "Yellow";
		break;
	case 3:
		temp = "Black";
		break;
	case 4:
		temp = "Red";
		break;
	default:
		temp = "";
		break;
	}

	cout << "Location name: " << name << endl << "Location region: " << temp << endl;
}
