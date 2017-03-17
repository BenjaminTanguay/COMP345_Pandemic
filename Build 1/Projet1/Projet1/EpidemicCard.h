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
	string const title = "Epidemic";
	virtual void read();
	string virtual getTitle();
};

