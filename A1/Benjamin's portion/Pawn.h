#pragma once
#include "City.h"
#include <string>
#include <iostream>
using namespace std;

class Pawn
{
public:
	Pawn(const string color, const City & origin);
	~Pawn();

	City & getCity();
	void setCity(const City & city);

	string & getColor();
	void setColor(const string color);

	void displayInfo();

private:

	// City is always a reference because always populated as a reference to another object city.
	City city;
	string color;
};

