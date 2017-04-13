#pragma once
#include "CommandActionCards.h"
#include "GameStateVar.h"
class OneQuietNight :
	public CommandActionCards
{
public:
	OneQuietNight();
	~OneQuietNight();
	void execute();
};

