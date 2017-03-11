#include "EpidemicCard.h"



EpidemicCard::EpidemicCard()
{
	this->description = "1-INCREASE\nMove the infection rate marker forward 1 space\n\n2-INFECT\nDraw the bottom card from the infection deck and put 3 cubes on that city. Discard that card\n\n3-INTENSIFY\nShuffle the cards in the infection discard pile and put them on top of the infection deck";
}


EpidemicCard::~EpidemicCard()
{
}

string EpidemicCard::getDescription()
{
	return description;
}

void EpidemicCard::read()
{
	cout << description << endl;
}
