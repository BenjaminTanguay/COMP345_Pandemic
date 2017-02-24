#pragma once
#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

class EpidemicCard :
	public Card
{
private:
	string description;
public:
	EpidemicCard();
	~EpidemicCard();

	string getDescription();

	virtual void read();
};

