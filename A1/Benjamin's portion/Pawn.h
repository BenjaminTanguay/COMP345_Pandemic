#pragma once
#include "City.h"
#include <string>
#include <iostream>
using namespace std;

class Pawn
{
private:

	// City is always a reference because always populated as a reference to another object city.
	City city;

	// Eventually, if we have a GUI, the color may become a hex code.
	string color;

public:

	Pawn(const string color, const City & origin);

	// Getters and setters. Here we use references instead of pointers to get used to both techniques.
	City & getCity();
	void setCity(const City & city);

	string & getColor();
	void setColor(const string color);

	// Here for demonstration purpose.
	void displayInfo();
};

