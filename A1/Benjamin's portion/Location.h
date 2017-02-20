#pragma once
#include <iostream>
#include <String>
using namespace std;
class Location
{
public:
	static const int BLUE = 1;
	static const int YELLOW = 2;
	static const int BLACK = 3;
	static const int RED = 4;
	Location();
	Location(const string name, const int region);

	~Location();

	string getName();
	int getRegion();

	void setName(const string name);
	void setRegion(const int region);
	void displayInfo();
private:
	string name;
	int region;


};

