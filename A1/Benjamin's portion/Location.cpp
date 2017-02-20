#include "Location.h"



Location::Location()
{
}

Location::Location(const string name, const int region)
{
	this->name = name;
	this->region = region;
}


Location::~Location()
{
}

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
