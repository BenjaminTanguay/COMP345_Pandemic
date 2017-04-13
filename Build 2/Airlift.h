#pragma once
#include "CommandActionCards.h"
#include "Player.h"

using namespace std;

class Airlift :
	public CommandActionCards
{
private:
	Player * player;
	City * city;
public:
	Airlift(Player * player, City * city);
	~Airlift();

	void execute();
};

