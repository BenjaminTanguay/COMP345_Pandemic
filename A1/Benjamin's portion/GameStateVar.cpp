#include "GameStateVar.h"



GameStateVar::GameStateVar()
{
	this->blue = 24;
	this->yellow = 24;
	this->black = 24;
	this->red = 24;
	this->infectionRate = 2;
	this->infectionCounter = 1;
	this->eclosionCounter = 0;
	this->blueCure = false;
	this->yellowCure = false;
	this->blackCure = false;
	this->redCure = false;
}


GameStateVar::~GameStateVar()
{
}

bool GameStateVar::decrementCube(int region)
{
	switch (region) {
	case 1:
		--blue;
		if (blue >= 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		--yellow;
		if (yellow >= 0) {
			return true;
		}
		else {
			return false;
		}
		break;

	case 3:
		--black;
		if (black >= 0) {
			return true;
		}
		else {
			return false;
		}
		break;

	case 4:
		--red;
		if (red >= 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		return false;
	}
}

bool GameStateVar::incrementEclosion()
{
	++eclosionCounter;
	this->incrementInfection();
	if (eclosionCounter == 8) {
		return false;
	}
	else {
		return true;
	}
	return false;
}

void GameStateVar::incrementInfection()
{
	++infectionCounter;
	switch (infectionCounter) {
	case 1:
		infectionRate = 2;
		break;
	case 2:
		infectionRate = 2;
		break;
	case 3:
		infectionRate = 2;
		break;
	case 4:
		infectionRate = 3;
		break;
	case 5:
		infectionRate = 3;
		break;
	case 6:
		infectionRate = 4;
		break;
	case 7:
		infectionRate = 4;
		break;
	default:
		infectionRate = 4;
		break;
	}
}

int GameStateVar::getBlue()
{
	return this->blue;
}

int GameStateVar::getYellow()
{
	return this->yellow;
}

int GameStateVar::getBlack()
{
	return this->black;
}

int GameStateVar::getRed()
{
	return this->red;
}

int GameStateVar::getEclosionCounter()
{
	return this->eclosionCounter;
}

int GameStateVar::getInfectionRate()
{
	return this->infectionRate;
}

int GameStateVar::getInfectionCounter()
{
	return this->infectionCounter;
}

bool GameStateVar::getCure(int region)
{
	switch (region) {
	case 1:
		return blueCure;
	case 2:
		return yellowCure;
	case 3:
		return blackCure;
	case 4:
		return redCure;
	default:
		return false;
	}
}

bool GameStateVar::setCure(int region)
{
	switch (region) {
	case 1:
		blueCure = true;
		break;
	case 2:
		yellowCure = true;
		break;
	case 3:
		blackCure = true;
		break;
	case 4:
		redCure = true;
		break;
	default:
		break;
	}
	return !(blueCure && yellowCure && blackCure && redCure);
}
