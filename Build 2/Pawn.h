#pragma once
#include "City.h"
#include <string>
#include <iostream>
using namespace std;

class Pawn
{
private:

	// City is always a reference because always populated as a reference to another object city.
	City * city;

public:

	Pawn(City * origin);

	// Getters and setters. Here we use references instead of pointers to get used to both techniques.
	City * getCity();
	void setCity(City * city);

	// Here for demonstration purpose.
	void displayInfo();
};

